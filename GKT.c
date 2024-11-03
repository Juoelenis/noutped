#include <gtk/gtk.h>


GtkWidget *text_view;
GtkWidget *window;
GtkTextBuffer *text_buffer;


void open_file(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_OPEN,
                                         "Cancel", GTK_RESPONSE_CANCEL,
                                         "Open", GTK_RESPONSE_ACCEPT, NULL);


    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        char *content;
        gsize length;


        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if (g_file_get_contents(filename, &content, &length, NULL)) {
            gtk_text_buffer_set_text(text_buffer, content, length);
            g_free(content);
        }
        g_free(filename);
    }


    gtk_widget_destroy(dialog);
}


void save_file(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "Cancel", GTK_RESPONSE_CANCEL,
                                         "Save", GTK_RESPONSE_ACCEPT, NULL);


    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkTextIter start, end;
        gchar *content;


        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_text_buffer_get_bounds(text_buffer, &start, &end);
        content = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
        
        g_file_set_contents(filename, content, -1, NULL);
        
        g_free(filename);
        g_free(content);
    }


    gtk_widget_destroy(dialog);
}


void close_application(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}


int main(int argc, char *argv[]) {
    GtkWidget *vbox;
    GtkWidget *menubar;
    GtkWidget *file_menu;
    GtkWidget *file_menu_item;
    GtkWidget *open_item;
    GtkWidget *save_item;
    GtkWidget *exit_item;


    gtk_init(&argc, &argv);


    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(close_application), NULL);


    // Create text view and buffer
    text_view = gtk_text_view_new();
    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));


    // Create vertical box layout
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);


    // Create menu bar
    menubar = gtk_menu_bar_new();


    // File menu
    file_menu = gtk_menu_new();
    file_menu_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);


    // File menu items
    open_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(open_item, "activate", G_CALLBACK(open_file), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), open_item);


    save_item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(save_item, "activate", G_CALLBACK(save_file), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), save_item);


    exit_item = gtk_menu_item_new_with_label("Exit");
    g_signal_connect(exit_item, "activate", G_CALLBACK(close_application), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);


    // Pack everything into window
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file_menu_item);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);


    gtk_widget_show_all(window);
    gtk_main();


    return 0;
}

