/* This file extracted from the GTK tutorial. */

/* notebook.c */

#include <gtk/gtk.h>

/* This function rotates the position of the tabs */
void rotate_book (GtkButton *button, GtkNotebook *notebook)
{
    gtk_notebook_set_tab_pos (notebook, (notebook->tab_pos +1) %4);
}

/* Add/Remove the page tabs and the borders */
void tabsborder_book (GtkButton *button, GtkNotebook *notebook)
{
    gint tval = FALSE;
    gint bval = FALSE;
    if (notebook->show_tabs == 0)
	    tval = TRUE; 
    if (notebook->show_border == 0)
	    bval = TRUE;
    
    gtk_notebook_set_show_tabs (notebook, tval);
    gtk_notebook_set_show_border (notebook, bval);
}

/* Remove a page from the notebook */
void remove_book (GtkButton *button, GtkNotebook *notebook)
{
    gint page;
    
    page = gtk_notebook_current_page(notebook);
    gtk_notebook_remove_page (notebook, page);
    /* Need to refresh the widget -- 
     This forces the widget to redraw itself. */
    gtk_widget_draw(GTK_WIDGET(notebook), NULL);
}

void delete (GtkWidget *widget, gpointer *data)
{
    gtk_main_quit ();
}

int main (int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *checkbutton;
    int i;
    char bufferf[32];
    char bufferl[32];
    
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
			GTK_SIGNAL_FUNC (delete), NULL);
    
    gtk_container_border_width (GTK_CONTAINER (window), 10);
    
    table = gtk_table_new(2,6,TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    
    /* Create a new notebook, place the position of the tabs */
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults(GTK_TABLE(table), notebook, 0,6,0,1);
    gtk_widget_show(notebook);
    
    /* lets append a bunch of pages to the notebook */
    for (i=0; i < 5; i++) {
	sprintf(bufferf, "Append Frame %d", i+1);
	sprintf(bufferl, "Page %d", i+1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_usize (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    }
    
    
    /* now lets add a page to a specific spot */
    checkbutton = gtk_check_button_new_with_label ("Check me please!");
    gtk_widget_set_usize(checkbutton, 100, 75);
    gtk_widget_show (checkbutton);
    
    label = gtk_label_new ("Add spot");
    gtk_container_add (GTK_CONTAINER (checkbutton), label);
    gtk_widget_show (label);
    label = gtk_label_new ("Add page");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), checkbutton, label, 2);
    
    /* Now finally lets prepend pages to the notebook */
    for (i=0; i < 5; i++) {
	sprintf(bufferf, "Prepend Frame %d", i+1);
	sprintf(bufferl, "PPage %d", i+1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_usize (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_prepend_page (GTK_NOTEBOOK(notebook), frame, label);
    }
    
    /* Set what page to start at (page 4) */
    gtk_notebook_set_page (GTK_NOTEBOOK(notebook), 3);
    
    
    /* create a bunch of buttons */
    button = gtk_button_new_with_label ("close");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       GTK_SIGNAL_FUNC (delete), NULL);
    gtk_table_attach_defaults(GTK_TABLE(table), button, 0,1,1,2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label ("next page");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       (GtkSignalFunc) gtk_notebook_next_page,
			       GTK_OBJECT (notebook));
    gtk_table_attach_defaults(GTK_TABLE(table), button, 1,2,1,2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label ("prev page");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       (GtkSignalFunc) gtk_notebook_prev_page,
			       GTK_OBJECT (notebook));
    gtk_table_attach_defaults(GTK_TABLE(table), button, 2,3,1,2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label ("tab position");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       (GtkSignalFunc) rotate_book, GTK_OBJECT(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table), button, 3,4,1,2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label ("tabs/border on/off");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       (GtkSignalFunc) tabsborder_book,
			       GTK_OBJECT (notebook));
    gtk_table_attach_defaults(GTK_TABLE(table), button, 4,5,1,2);
    gtk_widget_show(button);
    
    button = gtk_button_new_with_label ("remove page");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       (GtkSignalFunc) remove_book,
			       GTK_OBJECT(notebook));
    gtk_table_attach_defaults(GTK_TABLE(table), button, 5,6,1,2);
    gtk_widget_show(button);
    
    gtk_widget_show(table);
    gtk_widget_show(window);
    
    gtk_main ();
    
    return 0;
}