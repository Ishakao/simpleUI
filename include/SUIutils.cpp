#define API_LIB_EXPORT
#include "SUIutils.h"
#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#elif defined(__linux__)
#include <X11/XKBlib.h>
#include <gtk/gtk.h>
inline Display* d = XOpenDisplay(nullptr);
Window root = DefaultRootWindow(d);
#endif

extern "C" void SetConsoleUTF8() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
}

#ifdef _WIN32
extern "C" const wchar_t* GetFile() {
	static std::wstring result;
	wchar_t filename[MAX_PATH] = L"";

	OPENFILENAMEW ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = L"Images (*.jpg;*.jpeg;*.png)\0*.jpg;*.jpeg;*.png\0All files (*.*)\0*.*\0";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameW(&ofn)) {
		result = filename;
		return result.c_str();
	}
	return L"";
}
#elif defined(__linux__)
extern "C" const char* GetFile() {
	static std::string result;
	static bool inited = false;
	if (!inited) {
		inited = true;
		gtk_init(nullptr, nullptr);
	}

	GtkWidget* dialog = gtk_file_chooser_dialog_new(
		"Open Image",
		nullptr,
		GTK_FILE_CHOOSER_ACTION_OPEN,
		"_Cancel", GTK_RESPONSE_CANCEL,
		"_Open", GTK_RESPONSE_ACCEPT,
		nullptr
	);

	GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);

	GtkFileFilter* filter = gtk_file_filter_new();
	gtk_file_filter_set_name(filter, "Images (*.jpg, *.jpeg, *.png)");
	gtk_file_filter_add_pattern(filter, "*.jpg");
	gtk_file_filter_add_pattern(filter, "*.jpeg");
	gtk_file_filter_add_pattern(filter, "*.png");
	gtk_file_chooser_add_filter(chooser, filter);

	int response = gtk_dialog_run(GTK_DIALOG(dialog));

	if (response == GTK_RESPONSE_ACCEPT) {
		char* filename = gtk_file_chooser_get_filename(chooser);
		if (filename) {
			result = filename;
			g_free(filename);
		}
	} else {
		result = "";
	}

	gtk_widget_hide(dialog);
	gtk_widget_destroy(dialog);

	while (g_main_context_pending(nullptr)) {
		g_main_context_iteration(nullptr, FALSE);
	}

	return result.c_str();
}
#endif