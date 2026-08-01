/*
#include <simpleUI.h>
#include <mutex>
#include <thread>
#include <array>
#include <unordered_map>
#include <unordered_set>
#define MULTITHREADING

namespace fs = std::filesystem;
#if defined(_WIN32)
fs::path homeEnv = std::getenv("USERPROFILE");
#else
fs::path homeEnv = std::getenv("HOME");
#endif

const std::string reposDirectory = homeEnv.string() + "\\MyRepositories";
std::string currentRepository = "";
static FilePathList droppedFiles = {};
static std::vector<fs::path> filesToCopy;

size_t string_to_size_t(std::string s) {
	size_t n = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < '0' or s[i] > '9') {
			break;
		}

		n *= 10;
		n += s[i] - '0';
	}

	return n;
}

std::string exec(const std::string& cmd) {
	std::array<char, 4096> buffer;
	std::string result;

	std::string finalCmd = "cd /d " + currentRepository + "\\pushDir" + " && " + cmd;

	FILE* pipe = _popen(finalCmd.c_str(), "r");
	if (!pipe) {
		return "e1";
	}

	while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
		result += buffer.data();
	}

	_pclose(pipe);
	return result;
}

bool directoryExists(const std::string& path) {
	fs::path p = path;

	if (fs::exists(p) and fs::is_directory(p)) {
		return true;
	}
	return false;
}

bool fileExists(const std::string& path) {
	fs::path p = path;

	if (fs::exists(p) and fs::is_regular_file(p)) {
		return true;
	}
	return false;
}

std::mutex logMutex;
void writeLog(const std::string& repoName, const std::string& text) {
	logMutex.lock();
	if (directoryExists(repoName)) {
		std::ofstream logFile(repoName + "\\logFile.txt", std::ios::out | std::ios::app);
		if (logFile) {
			logFile << text;
			logFile.close();
		}
	}
	logMutex.unlock();
}

Instance* StartInstance = nullptr;
Object2D* Repositories = nullptr;
Object2D* Background = nullptr;
Object2D* CreateRepository = nullptr;
Object2D* RepositoryManagement = nullptr;
ScrollFrame* RepositoriesScroll = nullptr;
float baseAnimationTime = 0.25;
fs::path exePath = "";
void openRepositories();
void openRepositoryManagement(const std::string&);

std::mutex ImagesLoadingMtx;
std::unordered_map<std::string, Image> loadedImages;
void loadImage(const std::string& name, const std::string& path) {
	ImagesLoadingMtx.lock();
	loadedImages.insert({ name, LoadImage(path.c_str()) });
	ImagesLoadingMtx.unlock();
}

void unloadImage(const std::string& name) {
	ImagesLoadingMtx.lock();

	auto it = loadedImages.find(name);
	if (it != loadedImages.end()) {
		UnloadImage(it->second);
		loadedImages.erase(it);
	}

	ImagesLoadingMtx.unlock();
}

Image getImage(const std::string& name) {
	ImagesLoadingMtx.lock();
	auto it = loadedImages.find(name);
	if (it != loadedImages.end()) {
		ImagesLoadingMtx.unlock();
		return it->second;
	}
	ImagesLoadingMtx.unlock();

	throw "Image not found";
}

enum InfoMessageType {
	SUCCESS = 0,
	WARN,
	ERROR
};

void SendInfoMessage(const std::string& title, const std::string& text, InfoMessageType type) {
	if (!StartInstance) return;

	static std::mutex mtx;

	Color color = (type == SUCCESS ? Color{ 141, 233, 147, 255 } : ((type == WARN) ? Color{ 243, 187, 31, 255 } : Color{ 228, 106, 92, 255 }));
	static std::vector<Object2D*> messages;
	Object2D* msg = new Object2D(StartInstance);
	msg->BackgroundColor = { 60,60,60,255 };
	msg->ZIndex = 999;
	msg->BorderColor = color;
	msg->BorderThickness = 3;
	msg->Position = { 1, 0.895 };
	msg->SizeOFFSET = { 225, 75 };
	msg->PositionOFFSET = { 15, -85 };
	msg->Roundness = 0.2;
	msg->BackgroundTransparency = 0.4;
	msg->BorderTransparency = 0.4;
	TextLabel* tit = new TextLabel(msg);
	tit->Size = { 1, 0.35 };
	tit->TextAnchor = TextAnchorEnum::W;
	tit->SetText(" " + title + " ");
	tit->TextColor = color;
	tit->TextTransparency = 0.3;
	tit->SetFont("SegoeB");
	tit->BackgroundTransparency = 1;
	TextLabel* tex = new TextLabel(msg);
	tex->Size = { 1, 0.65 };
	tex->Position = { 0, 0.35 };
	tex->TextAnchor = TextAnchorEnum::NW;
	tex->SetText(" " + text + " ");
	tex->TextColor = color;
	tex->TextTransparency = 0.3;
	tex->SetFont("SegoeB");
	tex->BackgroundTransparency = 1;

	Animate::Create(&msg->PositionOFFSET.x, baseAnimationTime, -250);
	mtx.lock();
	for (int i = 0; i < messages.size(); i++) {
		Object2D* m = messages[i];
		Animate::Create(&m->PositionOFFSET.y, 0.125, -85 * ((long)messages.size() - i + 1));
	}
	messages.push_back(msg);
	mtx.unlock();

	new Tasks::Task(4, [msg]() {
		mtx.lock();
		for (int i = 0; i < messages.size(); i++) {
			Object2D* m = messages[i];
			if (m == msg) {
				messages.erase(messages.begin() + i);
				auto a = Animate::Create(&m->PositionOFFSET.x, 0.15, 15);
				a->Completed = [m]() {
					Delete(m);
					};
				break;
			}
		}
		mtx.unlock();
	});
}

void updateRepositories() {
	constexpr static int SizeY = 70;

	if (!Repositories or !RepositoriesScroll) return;
	RepositoriesScroll->CanvasSizeOFFSET.y = 0;
	RepositoriesScroll->findChild("Folder")->deleteAllChildren();

	if (!directoryExists(reposDirectory)) {
		fs::create_directory(reposDirectory);
	}

	std::vector<fs::directory_entry> entries;
	for (const auto& entry : fs::directory_iterator(reposDirectory)) {
		if (entry.is_directory() and fileExists(entry.path().string() + "\\RepoData.rpd")) {
			auto e = entry;
			e.refresh();
			entries.push_back(e);
		}
	}

	std::sort(entries.begin(), entries.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
		return fs::last_write_time(a) > fs::last_write_time(b);
	});

	int i = 0;

	for (const auto& entry : entries) {
		Object2D* rep = new Object2D(RepositoriesScroll->findChild("Folder"));
		rep->PositionOFFSET.y = i * SizeY;
		rep->SizeOFFSET = { 0, SizeY };
		rep->Size.x = 1;
		rep->BackgroundColor = { 50,50,50,255 };
		rep->Active = true;
		rep->Name = entry.path().string();
		rep->AddEvent(MOUSE_ENTER, [](Object2D* t) {
			Animate::Create(&t->BackgroundColor, 0.15, { 30,30,30,255 });
		});
		rep->AddEvent(MOUSE_LEAVE, [](Object2D* t) {
			Animate::Create(&t->BackgroundColor, 0.15, { 50,50,50,255 });
		});
		rep->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			openRepositoryManagement(t->Name);
		}, LEFT);

		TextLabel* name = new TextLabel(rep);
		name->Size = { 1, 0 };
		name->SizeOFFSET = { 0, 30 };
		name->SetFont("SegoeB");
		name->SetText(" " + std::string(reinterpret_cast<const char*>(entry.path().filename().u8string().c_str())));
		name->TextColor = { 125, 170, 220, 255 };
		name->TextAnchor = TextAnchorEnum::W;
		name->BackgroundTransparency = 1;

		int filesQ = 0;
		size_t size = 0;
		for (const auto& ent : fs::recursive_directory_iterator(entry.path() / "src")) {
			if (ent.is_regular_file()) {
				if (ent.path().filename() != "logFile.txt" and ent.path().filename() != "RepoData.rpd") {
					filesQ++;
					size += ent.file_size();
				}
			}
		}

		TextLabel* filesQuantity = new TextLabel(rep);
		filesQuantity->Size = { 0.4, 0 };
		filesQuantity->SizeOFFSET = { 0, 30 };
		filesQuantity->PositionOFFSET = { 0, -30 };
		filesQuantity->Position = { 0, 1 };
		filesQuantity->SetFont("SegoeB");
		filesQuantity->SetText(" Файлов: " + std::to_string(filesQ));
		filesQuantity->TextColor = { 120,120,120,255 };
		filesQuantity->TextAnchor = TextAnchorEnum::W;
		filesQuantity->BackgroundTransparency = 1;

		TextLabel* filesSize = new TextLabel(rep);
		filesSize->Size = { 0.5, 0 };
		filesSize->SizeOFFSET = { 0, 30 };
		filesSize->PositionOFFSET = { 0, -30 };
		filesSize->Position = { 0.5, 1 };
		filesSize->SetFont("SegoeB");
		filesSize->SetText(" Размер: " + std::to_string(size / 1024 / 1024) + "MB");
		filesSize->TextColor = { 120,120,120,255 };
		filesSize->TextAnchor = TextAnchorEnum::W;
		filesSize->BackgroundTransparency = 1;

		i++;
	}

	RepositoriesScroll->CanvasSizeOFFSET.y = entries.size() * SizeY;

	static_cast<TextLabel*>(RepositoriesScroll->findChild("Zero"))->Visible = !entries.size();
}

bool animation = false;

void mainMenu() {
	if (animation) return;
	filesToCopy.clear();

	Background->ZIndex = 2;
	Repositories->ZIndex = 1;
	if (CreateRepository) CreateRepository->ZIndex = 1;
	if (RepositoryManagement) RepositoryManagement->ZIndex = 1;

	Background->Position = { 1, 0 };
	Animate::Create(&Background->Position.x, baseAnimationTime, 0);
	animation = true;
	new Tasks::Task(baseAnimationTime, []() {
		animation = false;
		if (RepositoryManagement and RepositoryManagement->findChild("ierarchy")) {
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ierarchy"))->deleteAllChildren();
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ierarchy"))->CanvasSizeOFFSET.y = 0;
		}

		if (RepositoryManagement and RepositoryManagement->findChild("ScrollFrame")) {
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->deleteAllChildren();
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->CanvasSizeOFFSET.y = 0;
		}
	});

	if (CreateRepository and CreateRepository->findChildOfClass(SCROLLFRAME)) {
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->deleteAllChildren();
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->CanvasSizeOFFSET.y = 0;
	}
}

void openRepositoryManagement(const std::string& name) {
	if (animation) return;
	static ScrollFrame* ierarchy = nullptr;
	currentRepository = name;
	filesToCopy.clear();

	auto updateIerarchy = []() {
		if (ierarchy) {
			ierarchy->deleteAllChildren();
			ierarchy->CanvasSizeOFFSET.y = 0;
			int maxDepth = 0;
			static std::function<void(fs::path, int)> goDeep = [&maxDepth](fs::path currentPath, int depth) {
				for (const auto& entry : fs::directory_iterator(currentPath)) {
					TextLabel* parentalObj = new TextLabel(ierarchy);
					float lerp = (float)depth / 10; if (lerp > 1) lerp = 1;
					parentalObj->BackgroundTransparency = (1 - std::lerp(0, 0.5, lerp));
					parentalObj->PositionOFFSET = { depth * 35.0f, (ierarchy->Children.size() - 1) * 40.0f };
					parentalObj->SetFont("SegoeB");
					parentalObj->SizeOFFSET = { 300, 40 };
					parentalObj->Roundness = 0.2;
					parentalObj->TextAnchor = TextAnchorEnum::W;
					parentalObj->MaxVisibleSymbols = 30;
					parentalObj->MaxVisibleRight = true;
					parentalObj->TextColor = (fs::is_directory(entry) ? Color{ 255, 255, 204, 255 } : Color{ 180, 180, 180, 255 });
					auto u8Str = entry.path().filename().u8string();
					parentalObj->SetText(std::string(reinterpret_cast<const char*>(u8Str.data()), u8Str.size()));

					if (fs::is_directory(entry)) {

						goDeep(entry.path(), depth + 1);
					}
				}

				if (depth > maxDepth) {
					maxDepth = depth;
				}
			};

			if (!directoryExists(currentRepository + "\\src")) {
				fs::create_directory(currentRepository + "\\src");
			}
			goDeep(fs::path(currentRepository + "\\src"), 0);
			ierarchy->CanvasSizeOFFSET = { 35.0f * maxDepth + 300, (float)ierarchy->Children.size() * 40 };
		}
	};

	if (!RepositoryManagement) {
		RepositoryManagement = new Object2D(StartInstance);
		RepositoryManagement->BackgroundColor = { 30,30,30,255 };
		RepositoryManagement->Size = { 1, 1 };
		RepositoryManagement->Active = true;

		ImageLabel* back = new ImageLabel(RepositoryManagement);
		back->Active = true;
		back->Position = { 0, 0.01 };
		back->Size = { 0.04, 0.03 };
		back->setImage(getImage("backArrow"));
		back->BackgroundTransparency = 1;
		back->ImageColor = { 150,150,150,255 };
		back->AddEvent(MOUSE_ENTER, [back](Object2D* t) {
			Animate::Create(&back->ImageColor, 0.15, { 230,230,230, 255 });
		});
		back->AddEvent(MOUSE_LEAVE,[back](Object2D* t) {
			Animate::Create(&back->ImageColor, 0.15, { 150,150,150,255 });
		});
		back->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			currentRepository = "";
			openRepositories();
		}, LEFT);

		TextLabel* upperName = new TextLabel(RepositoryManagement);
		upperName->BackgroundTransparency = 1;
		upperName->AnchorPosition = { 0.5,0.5 };
		upperName->Position = { 0.5,0.04 };
		upperName->Size = { 0.4, 0.05 };
		upperName->SetFont("SegoeB");
		upperName->Name = "upperName";
		upperName->Active = true;
		upperName->TextColor = { 110, 155, 200, 255 };
		upperName->AddEvent(MOUSE_ENTER, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 125, 170, 220, 255 });
		});
		upperName->AddEvent(MOUSE_LEAVE, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 110, 155, 200, 255 });
		});

		TextLabel* ierarchyText = new TextLabel(RepositoryManagement);
		ierarchyText->BackgroundTransparency = 1;
		ierarchyText->Position = { 0.04,0.1 };
		ierarchyText->Size = { 0.28, 0.06 };
		ierarchyText->SetText("Files ierarchy");
		ierarchyText->SetFont("SegoeB");
		ierarchyText->Name = "upperName";
		ierarchyText->TextColor = { 125, 170, 220, 255 };

		ierarchy = new ScrollFrame(RepositoryManagement);
		ierarchy->Position = { 0.04, 0.16 };
		ierarchy->Size = { 0.28, 0.8 };
		ierarchy->BackgroundColor = { 70,70,70,255 };
		ierarchy->BorderColor = { 80,80,80,255 };
		ierarchy->BorderThickness = 4;
		ierarchy->ScrollSpeed = 0;
		ierarchy->ScrollSpeedOFFSET = 350;
		ierarchy->Animated = true;
		ierarchy->Name = "ierarchy";
		ierarchy->Active = true;
		ierarchy->Direction = 'B';
		ierarchy->SliderColor = { 125, 170, 220, 255 };
		ierarchy->AddEvent(MOUSE_ENTER, [](Object2D* t) {
			Animate::Create(&ierarchy->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		ierarchy->AddEvent(MOUSE_LEAVE, [](Object2D* t) {
			Animate::Create(&ierarchy->BorderColor, 0.15, { 80,80,80,255 });
		});

		TextLabel* updateText = new TextLabel(RepositoryManagement);
		updateText->Position = { 0.33, 0.16 };
		updateText->PositionOFFSET = { 0, 50 };
		updateText->SizeOFFSET = { 0, 40 };
		updateText->Size = { 0.2, 0 };
		updateText->SetText("Update data");
		updateText->TextAnchor = TextAnchorEnum::W;
		updateText->SetFont("SegoeB");
		updateText->TextColor = { 125, 170, 220, 255 };
		updateText->BackgroundTransparency = 1;
		updateText->TextTransparency = 1;

		ImageLabel* update = new ImageLabel(RepositoryManagement);
		update->Position = { 0.33, 0.16 };
		update->PositionOFFSET = { 0, 0 };
		update->BackgroundColor = { 90, 90, 90, 255 };
		update->SizeOFFSET = { 40, 40 };
		update->ImageColor = { 50,50,50,255 };
		update->setImage(getImage("update"));
		update->BorderColor = { 50,50,50,255 };
		update->BorderThickness = 2;
		update->Active = true;
		update->Overlay = FIT;
		update->AddEvent(MOUSE_ENTER, [update, updateText](Object2D* t) {
			Animate::Create(&update->ImageColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&update->BorderColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&updateText->TextTransparency, 0.15, 0);
		});
		update->AddEvent(MOUSE_LEAVE, [update, updateText](Object2D* t) {
			Animate::Create(&update->ImageColor, 0.15, { 50,50,50,255 });
			Animate::Create(&update->BorderColor, 0.15, { 50,50,50,255 });
			Animate::Create(&updateText->TextTransparency, 0.15, 1);
		});
		update->AddEvent(MOUSE_CLICK, [updateIerarchy](Object2D* t) {
			try {
				updateIerarchy();
			} catch (const std::exception& e) {
				writeLog(currentRepository, "Error: " + std::string(e.what()) + "\n");
			}
		}, LEFT);

		TextLabel* deletingRepo = new TextLabel(RepositoryManagement);
		deletingRepo->Size = { 1,1 };
		deletingRepo->BackgroundColor = { 60,60,60,255 };
		deletingRepo->BackgroundTransparency = 0.3;
		deletingRepo->Active = true;
		deletingRepo->Visible = false;
		deletingRepo->ZIndex = 999;
		deletingRepo->SetFont("SegoeB");
		deletingRepo->TextColor = { 180,180,180,255 };
		deletingRepo->TextSize = 70;
		deletingRepo->SetText("Deleting a " + fs::path(currentRepository).filename().string() + " repository. Please wait");

		TextLabel* pushStart = new TextLabel(RepositoryManagement);
		pushStart->Size = { 1,1 };
		pushStart->BackgroundColor = { 60,60,60,255 };
		pushStart->BackgroundTransparency = 0.3;
		pushStart->Active = true;
		pushStart->Visible = false;
		pushStart->ZIndex = 999;
		pushStart->SetFont("SegoeB");
		pushStart->TextColor = { 180,180,180,255 };
		pushStart->TextSize = 70;
		pushStart->SetText("Pushing your commit. Please wait");

		static auto deleteRepository = [deletingRepo]() {
			try {
				deletingRepo->Visible = true;
				auto pathToRemove = currentRepository;

				std::thread([deletingRepo, pathToRemove]() {
					fs::remove_all(pathToRemove);

					deletingRepo->Visible = false;
					openRepositories();
				}).detach();
			} catch (const fs::filesystem_error& e) {
				writeLog(currentRepository, "Error: " + std::string(e.what()) + "\n");
			}
		};

		TextLabel* deleteRepoText = new TextLabel(RepositoryManagement);
		deleteRepoText->Position = { 1, 0 };
		deleteRepoText->PositionOFFSET = { -160, 10 };
		deleteRepoText->SizeOFFSET = { 100, 40 };
		deleteRepoText->SetText("Delete repo");
		deleteRepoText->TextAnchor = TextAnchorEnum::E;
		deleteRepoText->SetFont("SegoeB");
		deleteRepoText->TextColor = { 232, 109, 109, 255 };
		deleteRepoText->BackgroundTransparency = 1;
		deleteRepoText->TextTransparency = 1;

		ImageLabel* deleteRepo = new ImageLabel(RepositoryManagement);
		deleteRepo->Position = { 1, 0 };
		deleteRepo->PositionOFFSET = { -50, 10 };
		deleteRepo->BackgroundColor = { 90, 90, 90, 255 };
		deleteRepo->SizeOFFSET = { 40, 40 };
		deleteRepo->ImageColor = { 50,50,50,255 };
		deleteRepo->setImage(getImage("delete"));
		deleteRepo->BorderColor = { 50,50,50,255 };
		deleteRepo->BorderThickness = 2;
		deleteRepo->Active = true;
		deleteRepo->Overlay = FIT;
		deleteRepo->AddEvent(MOUSE_ENTER, [deleteRepo, deleteRepoText](Object2D* t) {
			Animate::Create(&deleteRepo->ImageColor, 0.15, { 232, 109, 109, 255 });
			Animate::Create(&deleteRepo->BorderColor, 0.15, { 232, 109, 109, 255 });
			Animate::Create(&deleteRepoText->TextTransparency, 0.15, 0);
		});
		deleteRepo->AddEvent(MOUSE_LEAVE, [deleteRepo, deleteRepoText](Object2D* t) {
			Animate::Create(&deleteRepo->ImageColor, 0.15, { 50,50,50,255 });
			Animate::Create(&deleteRepo->BorderColor, 0.15, { 50,50,50,255 });
			Animate::Create(&deleteRepoText->TextTransparency, 0.15, 1);
		});
		deleteRepo->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			deleteRepository();
		}, LEFT);

		TextLabel* pushCommandText = new TextLabel(RepositoryManagement);
		pushCommandText->Position = { 0.5, 0.13 };
		pushCommandText->Size = { 0.46, 0.06 };
		pushCommandText->SetText("Type on-push command");
		pushCommandText->TextAnchor = TextAnchorEnum::W;
		pushCommandText->SetFont("SegoeB");
		pushCommandText->TextColor = { 125, 170, 220, 255 };
		pushCommandText->BackgroundTransparency = 1;

		TextBox* pushCommand = new TextBox(RepositoryManagement);
		pushCommand->Type = Viewported;
		pushCommand->ClearOnClick = false;
		pushCommand->font = "SegoeB";
		pushCommand->TextColor = { 125, 170, 220, 255 };
		pushCommand->PlaceholderText = " current env: " + fs::path(name).filename().string() + "\\src\\";
		pushCommand->Position = { 0.5, 0.2 };
		pushCommand->Size = { 0.46, 0.07};
		pushCommand->CursorColor = { 125, 170, 220, 255 };
		pushCommand->BackgroundColor = { 60,60,60,255 };
		pushCommand->BorderColor = { 80,80,80,255 };
		pushCommand->BorderThickness = 2;
		pushCommand->maxSymbols = -1;
		pushCommand->TextAnchor = TextAnchorEnum::W;

		pushCommand->OnTextChanged([pushCommand](Object2D* t) {
			if (fileExists(currentRepository + "\\RepoData.rpd")) {
				std::ofstream rpd(currentRepository + "\\RepoData.rpd", std::ios::trunc | std::ios::out);
				if (rpd) {
					rpd << pushCommand->GetText();
					rpd.close();
				}
			}
		});

		ScrollFrame* dropFilesScroll = new ScrollFrame(RepositoryManagement);
		dropFilesScroll->Position = { 0.72, 0.3 };
		dropFilesScroll->Size = { 0.24, 0.4 };
		dropFilesScroll->BackgroundColor = { 70,70,70,255 };
		dropFilesScroll->BorderColor = { 80,80,80,255 };
		dropFilesScroll->BorderThickness = 4;
		dropFilesScroll->ScrollSpeed = 0;
		dropFilesScroll->ScrollSpeedOFFSET = 250;
		dropFilesScroll->Animated = true;
		dropFilesScroll->Active = true;
		dropFilesScroll->SliderColor = { 125, 170, 220, 255 };
		dropFilesScroll->AddEvent(MOUSE_ENTER, [dropFilesScroll](Object2D* t) {
			Animate::Create(&dropFilesScroll->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		dropFilesScroll->AddEvent(MOUSE_LEAVE, [dropFilesScroll](Object2D* t) {
			Animate::Create(&dropFilesScroll->BorderColor, 0.15, { 80,80,80,255 });
		});

		TextLabel* dropFiles = new TextLabel(RepositoryManagement);
		dropFiles->Position = { 0.35, 0.3 };
		dropFiles->Size = { 0.35, 0.4 };
		dropFiles->SetFont("SegoeB");
		dropFiles->SetText("       Drag and drop files       ");
		dropFiles->TextColor = { 180,180,180,255 };
		dropFiles->BackgroundColor = { 70,70,70,255 };
		dropFiles->BorderColor = { 80,80,80,255 };
		dropFiles->BorderThickness = 4;
		dropFiles->Active = true;
		dropFiles->TextAnchor = TextAnchorEnum::W;
		dropFiles->AddEvent(MOUSE_ENTER, [dropFiles](Object2D* t) {
			Animate::Create(&dropFiles->TextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&dropFiles->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		dropFiles->AddEvent(MOUSE_LEAVE, [dropFiles](Object2D* t) {
			Animate::Create(&dropFiles->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&dropFiles->BorderColor, 0.15, { 80,80,80,255 });
		});
		dropFiles->AddEvent(TICK, [dropFilesScroll](Object2D* t) {
			if (IsFileDropped() and RepositoryManagement->ZIndex == 2) {
				UnloadDroppedFiles(droppedFiles);
				droppedFiles = LoadDroppedFiles();

				static std::function<TextLabel* (const std::string&, int)> create = [dropFilesScroll](const std::string& text, int pos = -1) {
					TextLabel* file = new TextLabel(((pos == -1) ? dropFilesScroll : nullptr));
					file->Size = { 1, 0 };
					file->SizeOFFSET = { 0, 50 };
					file->PositionOFFSET = { 0, 50.0f * ((pos == -1) ? (dropFilesScroll->Children.size() - 1) : pos) };
					file->SetFont("SegoeB");
					file->SetText(text);
					file->BackgroundColor = { 60,60,60,255 };
					file->TextColor = { 180,180,180,255 };
					file->TextAnchor = TextAnchorEnum::W;
					file->MaxVisibleSymbols = 30;
					file->MaxVisibleRight = true;

					return file;
				};

				for (int i = 0; i < droppedFiles.count; i++) {
					fs::path path = droppedFiles.paths[i];
					filesToCopy.push_back(path);

					if (fs::is_directory(path)) {
						std::vector<fs::directory_entry> entries;
						for (const auto& ent : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
							if (fs::is_regular_file(ent)) {
								entries.push_back(ent);
							}
						}
						std::vector<TextLabel*> labels;
						labels.resize(entries.size());

						if (entries.size() > 200) {
						#ifdef MULTITHREADING
							int totalEntries = entries.size();
							int basePart = totalEntries / 4;
							int remainder = totalEntries % 4;
							int currentLower = 0;

							std::vector<std::thread*> workingThreads;
							workingThreads.resize(4);
							for (int i = 0; i < 4; i++) {
								std::thread* t = new std::thread([entries, &labels, i, &currentLower, remainder, basePart, totalEntries]() {
									int partSize = basePart + (i < remainder ? 1 : 0);
									int lower = currentLower;
									int upper = lower + partSize;
									currentLower = upper;

									if (lower >= totalEntries) return;

									for (int z = lower; z < upper and z < entries.size(); z++) {
										const fs::directory_entry& entry = entries[z];
										TextLabel* l = create(reinterpret_cast<const char*>(entry.path().u8string().c_str()), z);
										labels[z] = l;
									}
								});

								workingThreads[i] = t;
							}
							for (auto t : workingThreads) {
								if (t->joinable()) {
									t->join();
								}
							}

							for (TextLabel* l : labels) {
								if (l == nullptr) continue;
								l->setParent(dropFilesScroll);
							}
						#else
							for (const auto& entry : entries) {
								create(reinterpret_cast<const char*>(entry.path().u8string().c_str()), -1);
							}
						#endif
						}
						else {
							for (const auto& entry : entries) {
								create(reinterpret_cast<const char*>(entry.path().u8string().c_str()), -1);
							}
						}
					}
					else {
						create(droppedFiles.paths[i], -1);
					}
				}

				dropFilesScroll->CanvasSizeOFFSET.y = dropFilesScroll->Children.size() * 50;
			}
		});

		Object2D* pushWindowBackground = new Object2D(RepositoryManagement);
		pushWindowBackground->ZIndex = 50;
		pushWindowBackground->Active = true;
		pushWindowBackground->BackgroundTransparency = 0.15;
		pushWindowBackground->Size = { 1,1 };
		pushWindowBackground->Visible = false;

		TextLabel* res = new TextLabel(pushWindowBackground);
		res->Position = { 0.5,0.02 };
		res->AnchorPosition = { 0.5, 0 };
		res->Size = { 0.9, 0.07 };
		res->SetFont("SegoeB");
		res->SetText("Push result");
		res->BackgroundTransparency = 1;
		res->TextColor = { 125, 170, 220, 255 };

		TextLabel* output = new TextLabel(pushWindowBackground);
		output->Position = { 0.5,0.1 };
		output->AnchorPosition = { 0.5, 0 };
		output->Size = { 0.8, 0.6 };
		output->TextAnchor = TextAnchorEnum::NW;
		output->SetFont("SegoeB");
		output->BackgroundColor = { 70,70,70,255 };
		output->BorderColor = { 90,90,90,255 };
		output->TextColor = { 125, 170, 220, 255 };
		output->BorderThickness = 3;
		output->Name = "output";
		output->TextSize = 30;
		output->AddEvent(MOUSE_ENTER, [output](Object2D* t) {
			Animate::Create(&output->TextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&output->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		output->AddEvent(MOUSE_LEAVE, [output](Object2D* t) {
			Animate::Create(&output->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&output->BorderColor, 0.15, { 80,80,80,255 });
		});

		TextLabel* pushAccept = new TextLabel(pushWindowBackground);
		pushAccept->Position = { 0.3, 0.8 };
		pushAccept->AnchorPosition = { 0.5, 0 };
		pushAccept->Size = { 0.25, 0.1 };
		pushAccept->SetFont("SegoeB");
		pushAccept->SetText(" Accept push ");
		pushAccept->TextColor = { 180,180,180,255 };
		pushAccept->BackgroundColor = { 70,70,70,255 };
		pushAccept->BorderColor = { 80,80,80,255 };
		pushAccept->BorderThickness = 3;
		pushAccept->Active = true;
		pushAccept->AddEvent(MOUSE_ENTER, [pushAccept](Object2D* t) {
			Animate::Create(&pushAccept->TextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&pushAccept->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		pushAccept->AddEvent(MOUSE_LEAVE, [pushAccept](Object2D* t) {
			Animate::Create(&pushAccept->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&pushAccept->BorderColor, 0.15, { 80,80,80,255 });
		});
		pushAccept->AddEvent(MOUSE_CLICK, [pushAccept, pushWindowBackground, updateIerarchy](Object2D* t) {
			for (const fs::path& p : filesToCopy) {
				if (fs::exists(p)) {
					fs::copy(p, currentRepository + "\\src", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
				}
			}

			SendInfoMessage("Push", "Successfully pushed!", SUCCESS);
			writeLog(currentRepository, "Successfully pushed!\n");
			pushWindowBackground->Visible = false;
			filesToCopy.clear();
			if (RepositoryManagement and RepositoryManagement->findChild("ScrollFrame")) {
				static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->deleteAllChildren();
				static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->CanvasSizeOFFSET.y = 0;
			}
			updateIerarchy();
		}, LEFT);

		TextLabel* pushDecline = new TextLabel(pushWindowBackground);
		pushDecline->Position = { 0.7, 0.8 };
		pushDecline->AnchorPosition = { 0.5, 0 };
		pushDecline->Size = { 0.25, 0.1 };
		pushDecline->SetFont("SegoeB");
		pushDecline->SetText(" Decline push ");
		pushDecline->TextColor = { 180,180,180,255 };
		pushDecline->BackgroundColor = { 70,70,70,255 };
		pushDecline->BorderColor = { 80,80,80,255 };
		pushDecline->BorderThickness = 3;
		pushDecline->Active = true;
		pushDecline->AddEvent(MOUSE_ENTER, [pushDecline](Object2D* t) {
			Animate::Create(&pushDecline->TextColor, 0.15, { 255,255,204, 255 });
			Animate::Create(&pushDecline->BorderColor, 0.15, { 255,255,204, 255 });
		});
		pushDecline->AddEvent(MOUSE_LEAVE, [pushDecline](Object2D* t) {
			Animate::Create(&pushDecline->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&pushDecline->BorderColor, 0.15, { 80,80,80,255 });
		});
		pushDecline->AddEvent(MOUSE_CLICK, [pushDecline, pushWindowBackground](Object2D* t) {
			pushWindowBackground->Visible = false;
			filesToCopy.clear();
			if (RepositoryManagement and RepositoryManagement->findChild("ScrollFrame")) {
				static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->deleteAllChildren();
				static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->CanvasSizeOFFSET.y = 0;
			}
			writeLog(currentRepository, "Push declined.\n");
		}, LEFT);

		TextLabel* push = new TextLabel(RepositoryManagement);
		push->Position = { 0.76, 0.9 };
		push->Size = { 0.2, 0.08 };
		push->SetFont("SegoeB");
		push->SetText(" Push ");
		push->TextColor = { 180,180,180,255 };
		push->BackgroundColor = { 70,70,70,255 };
		push->BorderColor = { 80,80,80,255 };
		push->BorderThickness = 3;
		push->Active = true;
		push->AddEvent(MOUSE_ENTER, [push](Object2D* t) {
			Animate::Create(&push->TextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&push->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		push->AddEvent(MOUSE_LEAVE, [push](Object2D* t) {
			Animate::Create(&push->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&push->BorderColor, 0.15, { 80,80,80,255 });
		});
		push->AddEvent(MOUSE_CLICK, [pushStart, pushCommand, pushWindowBackground](Object2D* t) {
			if (!filesToCopy.size()) {
				SendInfoMessage("Push error", "Nothing to push", WARN);
				writeLog(currentRepository, "Trying to push nothing. Push declined\n");
			} else {
				writeLog(currentRepository, "Push started. Copying files to test folder\n");
				try {
					pushStart->Visible = true;
					std::thread([pushStart, pushCommand, pushWindowBackground]() {
						fs::path repoPath(currentRepository);
						fs::path pushDir = repoPath / "pushDir";
						fs::path srcDir = repoPath / "src";

						try {
							if (fs::exists(pushDir)) {
								fs::remove_all(pushDir);
							}
							fs::create_directories(pushDir);

							if (fs::exists(srcDir)) {
								fs::copy(srcDir, pushDir, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
							}

							for (const fs::path& p : filesToCopy) {
								if (fs::exists(p)) {
									fs::copy(p, pushDir, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
								}
							}

							writeLog(currentRepository, "Files copied successfully\n");
							writeLog(currentRepository, "on-push command test starting\n");

							std::string result = exec(pushCommand->GetText());
							pushWindowBackground->Visible = true;
							static_cast<TextLabel*>(pushWindowBackground->findChild("output"))->SetText(result);
							if (fs::exists(pushDir)) {
								fs::remove_all(pushDir);
							}
							writeLog(currentRepository, "Push test completed. Result: " + result + "\n");
						} catch (const fs::filesystem_error& e) {
							writeLog(currentRepository, std::string("Filesystem error: ") + e.what() + "\n");
						} catch (const std::exception& e) {
							writeLog(currentRepository, std::string("General error: ") + e.what() + "\n");
						}

						pushStart->Visible = false;
					}).detach();
				} catch (const fs::filesystem_error& e) {
					writeLog(currentRepository, "Error: " + std::string(e.what()) + "\n");
				}
			}
		}, LEFT);
	}

	if (fileExists(currentRepository + "\\RepoData.rpd")) {
		std::ifstream rpd(currentRepository + "\\RepoData.rpd", std::ios::in);
		if (rpd) {
			std::stringstream buffer;
			buffer << rpd.rdbuf();
			if (static_cast<TextBox*>(RepositoryManagement->findChildOfClass(TEXTBOX))) {
				static_cast<TextBox*>(RepositoryManagement->findChildOfClass(TEXTBOX))->SetText(buffer.str());
			}
			rpd.close();
		}
	}

	static_cast<TextBox*>(RepositoryManagement->findChildOfClass(TEXTBOX))->PlaceholderText = " current env: " + fs::path(name).filename().string() + "\\src\\";
	static_cast<TextLabel*>(RepositoryManagement->findChild("upperName"))->SetText(fs::path(name).filename().string() + " management");

	updateIerarchy();

	if (CreateRepository and CreateRepository->findChildOfClass(SCROLLFRAME)) {
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->deleteAllChildren();
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->CanvasSizeOFFSET.y = 0;
	}

	if (CreateRepository) CreateRepository->ZIndex = 1;
	if (RepositoryManagement) RepositoryManagement->ZIndex = 2;
	Background->ZIndex = 1;
	Repositories->ZIndex = 1;

	RepositoryManagement->Position = { 1, 0 };
	Animate::Create(&RepositoryManagement->Position.x, baseAnimationTime, 0);
	animation = true;
	new Tasks::Task(baseAnimationTime, []() {
		animation = false;
	});
}

void openCreateRepository() {
	if (animation) return;
	filesToCopy.clear();

	if (!CreateRepository) {
		CreateRepository = new Object2D(StartInstance);
		CreateRepository->BackgroundColor = { 30,30,30,255 };
		CreateRepository->Size = { 1, 1 };
		CreateRepository->Active = true;

		TextLabel* creatingRepo = new TextLabel(CreateRepository);
		creatingRepo->Size = { 1,1 };
		creatingRepo->BackgroundColor = { 60,60,60,255 };
		creatingRepo->BackgroundTransparency = { 0.7 };
		creatingRepo->Active = true;
		creatingRepo->Visible = false;
		creatingRepo->ZIndex = 999;
		creatingRepo->SetFont("SegoeB");
		creatingRepo->TextColor = {180,180,180,255};
		creatingRepo->TextSize = 70;
		creatingRepo->SetText("Creating a new repository. Please wait");

		ImageLabel* back = new ImageLabel(CreateRepository);
		back->Active = true;
		back->Position = { 0, 0.01 };
		back->Size = { 0.04, 0.03 };
		back->setImage(getImage("backArrow"));
		back->BackgroundTransparency = 1;
		back->ImageColor = { 150,150,150,255 };
		back->AddEvent(MOUSE_ENTER, [back](Object2D* t) {
			Animate::Create(&back->ImageColor, 0.15, { 230,230,230, 255 });
		});
		back->AddEvent(MOUSE_LEAVE, [back](Object2D* t) {
			Animate::Create(&back->ImageColor, 0.15, { 150,150,150,255 });
		});
		back->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			openRepositories();
		}, LEFT);

		TextLabel* upperName = new TextLabel(CreateRepository);
		upperName->BackgroundTransparency = 1;
		upperName->AnchorPosition = { 0.5,0.5 };
		upperName->Position = { 0.5,0.04 };
		upperName->Size = { 0.4, 0.05 };
		upperName->Roundness = 0.2;
		upperName->SetText("Creating a repository");
		upperName->SetFont("SegoeB");
		upperName->Active = true;
		upperName->TextColor = { 110, 155, 200, 255 };
		upperName->AddEvent(MOUSE_ENTER, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 125, 170, 220, 255 });
		});
		upperName->AddEvent(MOUSE_LEAVE, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 110, 155, 200, 255 });
		});

		TextLabel* nameOfRepo = new TextLabel(CreateRepository);
		nameOfRepo->Position = {0.04, 0.1};
		nameOfRepo->Size = { 0.25, 0.06 };
		nameOfRepo->SetFont("SegoeB");
		nameOfRepo->SetText("Name of the new repository");
		nameOfRepo->TextColor = { 180,180,180,255 };
		nameOfRepo->BackgroundTransparency = 1;
		nameOfRepo->TextAnchor = TextAnchorEnum::W;

		TextBox* nameOfRepoTB = new TextBox(CreateRepository);
		nameOfRepoTB->Position = { 0.04, 0.165 };
		nameOfRepoTB->Size = { 0.4, 0.06 };
		nameOfRepoTB->maxSymbols = 40;
		nameOfRepoTB->PlaceholderTextColor = { 180,180,180,255 };
		nameOfRepoTB->TextColor = { 125, 170, 220, 255 };
		nameOfRepoTB->CursorColor = { 125, 170, 220, 255 };
		nameOfRepoTB->BackgroundColor = { 60,60,60,255 };
		nameOfRepoTB->BorderColor = { 80,80,80,255 };
		nameOfRepoTB->BorderThickness = 2;
		nameOfRepoTB->font = "SegoeB";
		nameOfRepoTB->PlaceholderText = " ...";
		nameOfRepoTB->TextAnchor = TextAnchorEnum::W;
		nameOfRepoTB->Type = Viewported;

		nameOfRepoTB->AddEvent(MOUSE_ENTER, [nameOfRepoTB](Object2D* t) {
			Animate::Create(&nameOfRepoTB->PlaceholderTextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&nameOfRepoTB->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		nameOfRepoTB->AddEvent(MOUSE_LEAVE, [nameOfRepoTB](Object2D* t) {
			Animate::Create(&nameOfRepoTB->PlaceholderTextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&nameOfRepoTB->BorderColor, 0.15, { 80,80,80,255 });
		});

		TextLabel* filesName = new TextLabel(CreateRepository);
		filesName->Position = { 0.68, 0.2 };
		filesName->Size = { 0.28, 0.06 };
		filesName->SetFont("SegoeB");
		filesName->SetText("Loaded files");
		filesName->TextColor = { 180,180,180,255 };
		filesName->BackgroundTransparency = 1;

		ScrollFrame* dropFilesScroll = new ScrollFrame(CreateRepository);
		dropFilesScroll->Position = { 0.68, 0.26 };
		dropFilesScroll->Size = { 0.28, 0.6 };
		dropFilesScroll->BackgroundColor = { 70,70,70,255 };
		dropFilesScroll->BorderColor = { 80,80,80,255 };
		dropFilesScroll->BorderThickness = 4;
		dropFilesScroll->ScrollSpeed = 0;
		dropFilesScroll->ScrollSpeedOFFSET = 250;
		dropFilesScroll->Animated = true;
		dropFilesScroll->Active = true;
		dropFilesScroll->SliderColor = { 125, 170, 220, 255 };
		dropFilesScroll->AddEvent(MOUSE_ENTER, [dropFilesScroll](Object2D* t) {
			Animate::Create(&dropFilesScroll->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		dropFilesScroll->AddEvent(MOUSE_LEAVE, [dropFilesScroll](Object2D* t) {
			Animate::Create(&dropFilesScroll->BorderColor, 0.15, { 80,80,80,255 });
		});

		TextLabel* dropFiles = new TextLabel(CreateRepository);
		dropFiles->Position = { 0.04, 0.26 };
		dropFiles->Size = { 0.6, 0.6 };
		dropFiles->SetFont("SegoeB");
		dropFiles->SetText("         Drag and drop files         ");
		dropFiles->TextColor = { 180,180,180,255 };
		dropFiles->BackgroundColor = { 70,70,70,255 };
		dropFiles->BorderColor = { 80,80,80,255 };
		dropFiles->BorderThickness = 4;
		dropFiles->Active = true;
		dropFiles->TextAnchor = TextAnchorEnum::W;
		dropFiles->AddEvent(MOUSE_ENTER, [dropFiles](Object2D* t) {
			Animate::Create(&dropFiles->TextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&dropFiles->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		dropFiles->AddEvent(MOUSE_LEAVE, [dropFiles](Object2D* t) {
			Animate::Create(&dropFiles->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&dropFiles->BorderColor, 0.15, { 80,80,80,255 });
		});
		dropFiles->AddEvent(TICK, [dropFilesScroll](Object2D* t) {
			if (IsFileDropped() and CreateRepository->ZIndex == 2) {
				UnloadDroppedFiles(droppedFiles);
				droppedFiles = LoadDroppedFiles();

				static std::function<TextLabel*(const std::string&, int)> create = [dropFilesScroll](const std::string& text, int pos = -1) {
					TextLabel* file = new TextLabel(((pos == -1) ? dropFilesScroll : nullptr));
					file->Size = { 1, 0 };
					file->SizeOFFSET = { 0, 50 };
					file->PositionOFFSET = { 0, 50.0f * ((pos == -1) ? (dropFilesScroll->Children.size() - 1) : pos) };
					file->SetFont("SegoeB");
					file->SetText(text);
					file->BackgroundColor = { 60,60,60,255 };
					file->TextColor = { 180,180,180,255 };
					file->TextAnchor = TextAnchorEnum::W;
					file->MaxVisibleSymbols = 30;
					file->MaxVisibleRight = true;

					return file;
				};

				for (int i = 0; i < droppedFiles.count; i++) {
					fs::path path = droppedFiles.paths[i];
					filesToCopy.push_back(path);

					if (fs::is_directory(path)) {
						std::vector<fs::directory_entry> entries;
						for (const auto& ent : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
							if (fs::is_regular_file(ent)) {
								entries.push_back(ent);
							}
						}
						std::vector<TextLabel*> labels;
						labels.resize(entries.size());

						if (entries.size() > 200) {
							#ifdef MULTITHREADING
								int totalEntries = entries.size();
								int basePart = totalEntries / 4;
								int remainder = totalEntries % 4;
								int currentLower = 0;

								std::vector<std::thread*> workingThreads;
								workingThreads.resize(4);
								for (int i = 0; i < 4; i++) {
									std::thread* t = new std::thread([entries, &labels, i, &currentLower, remainder, basePart, totalEntries]() {
										int partSize = basePart + (i < remainder ? 1 : 0);
										int lower = currentLower;
										int upper = lower + partSize;
										currentLower = upper;

										if (lower >= totalEntries) return;

										for (int z = lower; z < upper and z < entries.size(); z++) {
											const fs::directory_entry& entry = entries[z];
											TextLabel* l = create(reinterpret_cast<const char*>(entry.path().u8string().c_str()), z);
											labels[z] = l;
										}
									});

									workingThreads[i] = t;
								}
								for (auto t : workingThreads) {
									if (t->joinable()) {
										t->join();
									}
								}

								for (TextLabel* l : labels) {
									if (l == nullptr) continue;
									l->setParent(dropFilesScroll);
								}
							#else
								for (const auto& entry : entries) {
									create(reinterpret_cast<const char*>(entry.path().u8string().c_str()), -1);
								}
							#endif
						} else {
							for (const auto& entry : entries) {
								create(reinterpret_cast<const char*>(entry.path().u8string().c_str()), -1);
							}
						}
					} else {
						create(droppedFiles.paths[i], -1);
					}
				}

				dropFilesScroll->CanvasSizeOFFSET.y = dropFilesScroll->Children.size() * 50;
			}
		});

		TextLabel* Create = new TextLabel(CreateRepository);
		Create->Position = { 0.5, 0.9 };
		Create->AnchorPosition = { 0.5, 0 };
		Create->Size = { 0.2, 0.08 };
		Create->SetFont("SegoeB");
		Create->SetText(" Create ");
		Create->TextColor = { 180,180,180,255 };
		Create->BackgroundColor = { 70,70,70,255 };
		Create->BorderColor = { 80,80,80,255 };
		Create->BorderThickness = 3;
		Create->Active = true;
		Create->AddEvent(MOUSE_ENTER, [Create](Object2D* t) {
			Animate::Create(&Create->TextColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&Create->BorderColor, 0.15, { 125, 170, 220, 255 });
		});
		Create->AddEvent(MOUSE_LEAVE, [Create](Object2D* t) {
			Animate::Create(&Create->TextColor, 0.15, { 180,180,180,255 });
			Animate::Create(&Create->BorderColor, 0.15, { 80,80,80,255 });
		});
		Create->AddEvent(MOUSE_CLICK, [=](Object2D* t) {
			std::string additionalSuffix = "";
			while (true) {
				if (!directoryExists(reposDirectory + "\\" + (nameOfRepoTB->GetText().empty() ? "Repository" : nameOfRepoTB->GetText()) + additionalSuffix)) {
					break;
				}

				additionalSuffix = std::to_string(string_to_size_t(additionalSuffix) + 1);
			}

			std::string name = reposDirectory + "\\" + (nameOfRepoTB->GetText().empty() ? "Repository" : nameOfRepoTB->GetText()) + additionalSuffix;
			fs::create_directory(name);
			creatingRepo->Visible = true;

			std::ofstream rpdFile(name + "\\RepoData.rpd", std::ios::out | std::ios::app);
			if (rpdFile) {
				rpdFile.close();
			}

			std::ofstream logFile(name + "\\logFile.txt", std::ios::out | std::ios::app);
			if (logFile) {
				logFile << "Repository created successfully\n";
				logFile.close();
			}

			fs::create_directory(name + "\\src");
			fs::create_directory(name + "\\pushDir");

			try {
				for (const fs::path& p : filesToCopy) {
					fs::copy(p, name + "\\src", fs::copy_options::recursive | fs::copy_options::overwrite_existing);

					writeLog(name, "Successfully copied folder " + p.filename().string() + " recursively\n");
				}
			}
			catch (const fs::filesystem_error& e) {
				writeLog(name, "Error: " + std::string(e.what()) + "\n");
			}

			openRepositoryManagement(name);
			creatingRepo->Visible = false;
		}, LEFT);
	}

	filesToCopy.clear();
	if (CreateRepository and CreateRepository->findChildOfClass(SCROLLFRAME)) {
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->deleteAllChildren();
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->CanvasSizeOFFSET.y = 0;
	}

	if (CreateRepository and CreateRepository->findChildOfClass(TEXTBOX)) {
		static_cast<TextBox*>(CreateRepository->findChildOfClass(TEXTBOX))->SetText("");
	}

	if (CreateRepository) CreateRepository->ZIndex = 2;
	if (RepositoryManagement) RepositoryManagement->ZIndex = 1;
	Background->ZIndex = 1;
	Repositories->ZIndex = 1;

	CreateRepository->Position = { 1, 0 };
	Animate::Create(&CreateRepository->Position.x, baseAnimationTime, 0);
	animation = true;
	new Tasks::Task(baseAnimationTime, []() {
		animation = false;
		if (RepositoryManagement and RepositoryManagement->findChild("ierarchy")) {
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ierarchy"))->deleteAllChildren();
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ierarchy"))->CanvasSizeOFFSET.y = 0;
		}

		if (RepositoryManagement and RepositoryManagement->findChild("ScrollFrame")) {
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->deleteAllChildren();
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->CanvasSizeOFFSET.y = 0;
		}
	});
}

void openRepositories() {
	if (animation) return;
	filesToCopy.clear();

	if (!Repositories) {
		Repositories = new Object2D(StartInstance);
		Repositories->BackgroundColor = { 30,30,30,255 };
		Repositories->Size = { 1, 1 };
		Repositories->Active = true;

		ImageLabel* back = new ImageLabel(Repositories);
		back->Active = true;
		back->Position = { 0, 0.01 };
		back->Size = { 0.04, 0.03 };
		back->setImage(getImage("backArrow"));
		back->BackgroundTransparency = 1;
		back->ImageColor = { 150,150,150,255 };
		back->AddEvent(MOUSE_ENTER, [back](Object2D* t) {
			Animate::Create(&back->ImageColor, 0.15, { 230,230,230, 255 });
		});
		back->AddEvent(MOUSE_LEAVE, [back](Object2D* t) {
			Animate::Create(&back->ImageColor, 0.15, { 150,150,150,255 });
		});
		back->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			mainMenu();
		}, LEFT);

		TextLabel* upperName = new TextLabel(Repositories);
		upperName->BackgroundTransparency = 1;
		upperName->AnchorPosition = { 0.5,0.5 };
		upperName->Position = { 0.5,0.04 };
		upperName->Size = { 0.3, 0.05 };
		upperName->Roundness = 0.2;
		upperName->SetText("Your repositories");
		upperName->SetFont("SegoeB");
		upperName->Active = true;
		upperName->TextColor = { 110, 155, 200, 255 };
		upperName->AddEvent(MOUSE_ENTER, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 125, 170, 220, 255 });
		});
		upperName->AddEvent(MOUSE_LEAVE, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 110, 155, 200, 255 });
		});

		RepositoriesScroll = new ScrollFrame(Repositories);

		TextLabel* zeroRepos = new TextLabel(RepositoriesScroll);
		zeroRepos->Position = { 0.5, 0.5 };
		zeroRepos->AnchorPosition = { 0.5,0.5 };
		zeroRepos->Size = { 0.9, 0.2 };
		zeroRepos->Name = "Zero";
		zeroRepos->SetFont("SegoeB");
		zeroRepos->SetText("You don't have\n  repositories");
		zeroRepos->TextColor = { 80,80,80,255 };
		zeroRepos->BackgroundTransparency = 1;

		RepositoriesScroll->Position = { 0.04, 0.1 };
		RepositoriesScroll->Size = { 0.25, 0.8 };
		RepositoriesScroll->BackgroundColor = { 70,70,70,255 };
		RepositoriesScroll->BorderColor = { 80,80,80,255 };
		RepositoriesScroll->BorderThickness = 3;
		RepositoriesScroll->CanvasSizeOFFSET = { 0,0 };
		RepositoriesScroll->ScrollSpeedOFFSET = 150;
		RepositoriesScroll->ScrollSpeed = 0;
		RepositoriesScroll->SliderColor = { 125, 170, 220, 255 };
		RepositoriesScroll->CanBeEnteredIfNotHigher = true;
		RepositoriesScroll->Active = true;
		RepositoriesScroll->Animated = true;
		RepositoriesScroll->AddEvent(MOUSE_ENTER, [zeroRepos](Object2D* t) {
			Animate::Create(&RepositoriesScroll->BorderColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&zeroRepos->TextColor, 0.15, { 125, 170, 220, 255 });
		});
		RepositoriesScroll->AddEvent(MOUSE_LEAVE, [zeroRepos](Object2D* t) {
			Animate::Create(&RepositoriesScroll->BorderColor, 0.15, { 80,80,80,255 });
			Animate::Create(&zeroRepos->TextColor, 0.15, { 80,80,80,255 });
		});

		TextLabel* addRepoText = new TextLabel(Repositories);
		addRepoText->Position = { 0.3, 0.1 };
		addRepoText->PositionOFFSET = { 50, 0 };
		addRepoText->SizeOFFSET = { 0, 40 };
		addRepoText->Size = { 0.2, 0 };
		addRepoText->SetText("Add");
		addRepoText->TextAnchor = TextAnchorEnum::W;
		addRepoText->SetFont("SegoeB");
		addRepoText->TextColor = { 125, 170, 220, 255 };
		addRepoText->BackgroundTransparency = 1;
		addRepoText->TextTransparency = 1;

		ImageLabel* addRepo = new ImageLabel(Repositories);
		addRepo->Position = { 0.3, 0.1 };
		addRepo->BackgroundColor = { 90, 90, 90, 255 };
		addRepo->SizeOFFSET = { 40, 40 };
		addRepo->ImageColor = { 50,50,50,255 };
		addRepo->setImage(getImage("plus"));
		addRepo->BorderColor = { 50,50,50,255 };
		addRepo->BorderThickness = 2;
		addRepo->Active = true;
		addRepo->Overlay = FIT;
		addRepo->AddEvent(MOUSE_ENTER, [addRepo, addRepoText](Object2D* t) {
			Animate::Create(&addRepo->ImageColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&addRepo->BorderColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&addRepoText->TextTransparency, 0.15, 0);
		});
		addRepo->AddEvent(MOUSE_LEAVE, [addRepo, addRepoText](Object2D* t) {
			Animate::Create(&addRepo->ImageColor, 0.15, { 50,50,50,255 });
			Animate::Create(&addRepo->BorderColor, 0.15, { 50,50,50,255 });
			Animate::Create(&addRepoText->TextTransparency, 0.15, 1);
		});
		addRepo->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			openCreateRepository();
		}, LEFT);

		TextLabel* openFolderText = new TextLabel(Repositories);
		openFolderText->Position = { 0.3, 0.1 };
		openFolderText->PositionOFFSET = { 50, 50 };
		openFolderText->SizeOFFSET = { 0, 40 };
		openFolderText->Size = { 0.2, 0 };
		openFolderText->SetText("Open folder");
		openFolderText->TextAnchor = TextAnchorEnum::W;
		openFolderText->SetFont("SegoeB");
		openFolderText->TextColor = { 125, 170, 220, 255 };
		openFolderText->BackgroundTransparency = 1;
		openFolderText->TextTransparency = 1;

		ImageLabel* openFolder = new ImageLabel(Repositories);
		openFolder->Position = { 0.3, 0.1 };
		openFolder->PositionOFFSET = { 0, 50 };
		openFolder->BackgroundColor = { 90, 90, 90, 255 };
		openFolder->SizeOFFSET = { 40, 40 };
		openFolder->ImageColor = { 50,50,50,255 };
		openFolder->setImage(getImage("folder"));
		openFolder->BorderColor = { 50,50,50,255 };
		openFolder->BorderThickness = 2;
		openFolder->Active = true;
		openFolder->Overlay = FIT;
		openFolder->AddEvent(MOUSE_ENTER, [openFolder, openFolderText](Object2D* t) {
			Animate::Create(&openFolder->ImageColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&openFolder->BorderColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&openFolderText->TextTransparency, 0.15, 0);
		});
		openFolder->AddEvent(MOUSE_LEAVE, [openFolder, openFolderText](Object2D* t) {
			Animate::Create(&openFolder->ImageColor, 0.15, { 50,50,50,255 });
			Animate::Create(&openFolder->BorderColor, 0.15, { 50,50,50,255 });
			Animate::Create(&openFolderText->TextTransparency, 0.15, 1);
		});
		openFolder->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			#if defined(_WIN32)
				std::string command = "explorer \"" + reposDirectory + "\"";
				std::system(command.c_str());
			#elif defined(__APPLE__)
				std::string command = "open \"" + reposDirectory + "\"";
				std::system(command.c_str());
			#elif defined(__linux__)
				std::string command = "xdg-open \"" + reposDirectory + "\"";
				std::system(command.c_str());
			#endif
		}, LEFT);

		TextLabel* updateText = new TextLabel(Repositories);
		updateText->Position = { 0.3, 0.1 };
		updateText->PositionOFFSET = { 50, 100 };
		updateText->SizeOFFSET = { 0, 40 };
		updateText->Size = { 0.2, 0 };
		updateText->SetText("Update data");
		updateText->TextAnchor = TextAnchorEnum::W;
		updateText->SetFont("SegoeB");
		updateText->TextColor = { 125, 170, 220, 255 };
		updateText->BackgroundTransparency = 1;
		updateText->TextTransparency = 1;

		ImageLabel* update = new ImageLabel(Repositories);
		update->Position = { 0.3, 0.1 };
		update->PositionOFFSET = { 0, 100 };
		update->BackgroundColor = { 90, 90, 90, 255 };
		update->SizeOFFSET = { 40, 40 };
		update->ImageColor = { 50,50,50,255 };
		update->setImage(getImage("update"));
		update->BorderColor = { 50,50,50,255 };
		update->BorderThickness = 2;
		update->Active = true;
		update->Overlay = FIT;
		update->AddEvent(MOUSE_ENTER, [update, updateText](Object2D* t) {
			Animate::Create(&update->ImageColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&update->BorderColor, 0.15, { 125, 170, 220, 255 });
			Animate::Create(&updateText->TextTransparency, 0.15, 0);
			});
		update->AddEvent(MOUSE_LEAVE, [update, updateText](Object2D* t) {
			Animate::Create(&update->ImageColor, 0.15, { 50,50,50,255 });
			Animate::Create(&update->BorderColor, 0.15, { 50,50,50,255 });
			Animate::Create(&updateText->TextTransparency, 0.15, 1);
			});
		update->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			updateRepositories();
		}, LEFT);

		Folder* fold = new Folder(RepositoriesScroll);
	}

	updateRepositories();

	Background->ZIndex = 1;
	Repositories->ZIndex = 2;
	if (CreateRepository) CreateRepository->ZIndex = 1;
	if (RepositoryManagement) RepositoryManagement->ZIndex = 1;

	Repositories->Position = { 1, 0 };
	Animate::Create(&Repositories->Position.x, baseAnimationTime, 0);
	animation = true;
	new Tasks::Task(baseAnimationTime, []() {
		animation = false;
		if (RepositoryManagement and RepositoryManagement->findChild("ierarchy")) {
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ierarchy"))->deleteAllChildren();
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ierarchy"))->CanvasSizeOFFSET.y = 0;
		}

		if (RepositoryManagement and RepositoryManagement->findChild("ScrollFrame")) {
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->deleteAllChildren();
			static_cast<ScrollFrame*>(RepositoryManagement->findChild("ScrollFrame"))->CanvasSizeOFFSET.y = 0;
		}
	});

	if (CreateRepository and CreateRepository->findChildOfClass(SCROLLFRAME)) {
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->deleteAllChildren();
		static_cast<ScrollFrame*>(CreateRepository->findChildOfClass(SCROLLFRAME))->CanvasSizeOFFSET.y = 0;
	}
}

int main(int argc, char* argv[]) {
	try {
		std::locale::global(std::locale(".utf8"));
	} catch (const std::runtime_error&) {
		std::locale::global(std::locale("C"));
	}

	try {
		if (argc) {
			exePath = fs::absolute(argv[0]);
		}

		StartInstance = new Instance(true);

		addFontToQueqe("Segoe", "Fonts/segoeui.ttf", 100);
		addFontToQueqe("SegoeB", "Fonts/segoeuib.ttf", 60);
		loadImage("backArrow", "textures/arrow.png");
		loadImage("plus", "textures/plus.png");
		loadImage("update", "textures/update.png");
		loadImage("folder", "textures/folder.png");
		loadImage("delete", "textures/trashcan.png");
		SUI_SetMinimalWindowSize(800, 600);

		Background = new Object2D(StartInstance);
		Background->BackgroundColor = { 30,30,30,255 };
		Background->Size = { 1, 1 };
		Background->Active = true;

		TextLabel* upperName = new TextLabel(Background);
		upperName->BackgroundTransparency = 1;
		upperName->AnchorPosition = { 0.5,0.5 };
		upperName->Position = { 0.5,0.04 };
		upperName->Size = { 0.3, 0.05 };
		upperName->Roundness = 0.2;
		upperName->SetText("GitHub Actions");
		upperName->SetFont("SegoeB");
		upperName->Active = true;
		upperName->TextColor = { 110, 155, 200, 255 };
		upperName->AddEvent(MOUSE_ENTER, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 125, 170, 220, 255 });
		});
		upperName->AddEvent(MOUSE_LEAVE, [upperName](Object2D* t) {
			Animate::Create(&upperName->TextColor, 0.15, { 110, 155, 200, 255 });
		});

		TextLabel* repositoriesButton = new TextLabel(Background);
		repositoriesButton->Active = true;
		repositoriesButton->AnchorPosition = { 0.5, 0.5 };
		repositoriesButton->Position = { 0.5,0.3 };
		repositoriesButton->BackgroundColor = { 35, 35, 35, 255 };
		repositoriesButton->Roundness = 0.2;
		repositoriesButton->BorderThickness = 3;
		repositoriesButton->BorderColor = { 25,25,25,255 };
		repositoriesButton->Size = { 0.25, 0.075 };
		repositoriesButton->SetText("Repositories");
		repositoriesButton->SetFont("SegoeB");
		repositoriesButton->TextColor = { 70,70,70,255 };
		repositoriesButton->AddEvent(MOUSE_CLICK, [](Object2D* t) {
			openRepositories();
		}, LEFT);
		repositoriesButton->AddEvent(MOUSE_ENTER, [repositoriesButton](Object2D* t) {
			Animate::Create(&repositoriesButton->TextColor, 0.15, { 110, 155, 200, 255 });
			Animate::Create(&repositoriesButton->BorderColor, 0.15, { 40,60,90,255 });
			Animate::Create(&repositoriesButton->Size, 0.4, { 0.4, 0.1 }, Animate::Bounce, Animate::Out);
		});
		repositoriesButton->AddEvent(MOUSE_LEAVE, [repositoriesButton](Object2D* t) {
			Animate::Create(&repositoriesButton->TextColor, 0.15, { 70,70,70,255 });
			Animate::Create(&repositoriesButton->BorderColor, 0.15, { 25,25,25,255 });
			Animate::Create(&repositoriesButton->Size, 0.4, { 0.25, 0.075 }, Animate::Bounce, Animate::Out);
		});

		start(*StartInstance, { 1200, 700, 0 }, "GitHub Actions", "textures/icon.png", FLAG_WINDOW_RESIZABLE);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
*/


#include <simpleUI.h>

int main() {
	Instance* Root = new Instance(true); // True in constructor means that the object is rooted and it has no parents.
	Root->Name = "Root";

	TextLabel* Hello = new TextLabel(Root);
	Hello->AnchorPosition = { 0.5, 0.5 };
	Hello->Position = { 0.5, 0.5 };
	Hello->PositionOFFSET = { -350, 0 };
	Hello->SizeOFFSET = { 340, 80 };
	Hello->FontFace = "SegoeB";
	Hello->Text = " Hello ";
	Hello->Roundness = 0.2;
	Hello->Active = true;
	Hello->BorderThickness = 3;
	Hello->TextColor = { 224, 244, 244, 255 };
	Hello->BorderColor = { 0, 51, 25, 255 };
	Hello->BackgroundColor = { 0, 204, 0, 255 };
	Hello->AddEvent(MOUSE_ENTER, [Hello](Instance* th) {
		Animate::Create(&Hello->SizeOFFSET, 0.4, { 400, 100 }, Animate::Bounce, Animate::Out);
	});
	Hello->AddEvent(MOUSE_LEAVE, [Hello](Instance* th) {
		Animate::Create(&Hello->SizeOFFSET, 0.4, { 340, 80 }, Animate::Bounce, Animate::Out);
	});
	Hello->AddEvent(MOUSE_CLICK, [Hello](Instance* th) {Hello->Text += "1";}, LEFT);
	Hello->AddEvent(TEXT_CHANGED, [Hello](Instance* th) {std::cout << !Hello->Text << std::endl;}, LEFT);

	TextBox* World = new TextBox(Root);
	World->AnchorPosition = { 0.5, 0.5 };
	World->Position = { 0.5, 0.5 };
	World->PositionOFFSET = { 200, 0 };
	World->SizeOFFSET = { 340, 80 };
	World->FontFace = "SegoeB";
	World->Text = " World ";
	World->PlaceholderText = " World ";
	World->maxSymbols = 10;
	World->CursorColor = { 0, 102, 102, 255 };
	World->Roundness = 0.2;
	World->Active = true;
	World->BorderThickness = 3;
	World->TextColor = { 224, 244, 244, 255 };
	World->BackgroundColor = { 0, 102, 204, 255 };
	World->BorderColor = { 0, 102, 102, 255 };
	World->AddEvent(MOUSE_ENTER, [World](Instance* th) {
		Animate::Create(&World->SizeOFFSET, 0.4, { 400, 100 }, Animate::Bounce, Animate::Out);
	});
	World->AddEvent(MOUSE_LEAVE, [World](Instance* th) {
		Animate::Create(&World->SizeOFFSET, 0.4, { 340, 80 }, Animate::Bounce, Animate::Out);
	});
	World->AddEvent(CHILD_ADDED, [](Instance* th, Instance* child) {
		std::cout << "Child added " << child->Name << std::endl;
	});
	World->AddEvent(TEXT_CHANGED, [World](Instance* th) { std::cout << !World->Text << std::endl; });
	Hello->setParent(World);

	ALLOW_FPS = true; // Allows to show FPS label on F1
	ALLOW_DEBUG = true; // Allows to show debug menu on F2

	addFontToQueqe("SegoeB", "Fonts/segoeuib.ttf", 60); // Loading custom font
	SUI_SetMinimalWindowSize(600, 400);
	start(*Root, { 1200, 800, -1 }, "Test program", "Icon.ico", FLAG_WINDOW_RESIZABLE);
}