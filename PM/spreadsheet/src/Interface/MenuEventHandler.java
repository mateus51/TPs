package Interface;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.JFileChooser;
import javax.swing.JTable;
import javax.swing.filechooser.FileNameExtensionFilter;

import Persistencia.SpreadsheetExporter;


class MenuEventHandler implements ActionListener, ItemListener {

	private JTable table;
	Events action;

	MenuEventHandler(JTable table, Events action) {
		this.table = table;
		this.action = action;
	}

	public void actionPerformed(ActionEvent e) {
		System.out.println("action performed!\n" + e.getSource().getClass());
		System.out.println(e.getSource());

		FileNameExtensionFilter filter;
		SpreadsheetExporter exporter;
		JFileChooser chooser = new JFileChooser();
		int returnVal;

		switch (action) {
		case SAVE_FILE:
			exporter = new SpreadsheetExporter(table);
			filter = new FileNameExtensionFilter("Spreadsheet files", "sps");
			chooser.setFileFilter(filter);
			returnVal = chooser.showSaveDialog((Component) e.getSource());
			if(returnVal == JFileChooser.APPROVE_OPTION) {
				exporter.saveToFile(chooser.getSelectedFile());
			}
			break;
		case OPEN_FILE:
			filter = new FileNameExtensionFilter("Spreadsheet files", "sps");
			chooser.setFileFilter(filter);
			returnVal = chooser.showOpenDialog((Component) e.getSource());
			if(returnVal == JFileChooser.APPROVE_OPTION) {
				GUI.createNewTable(chooser.getSelectedFile());
			}
			break;
		case SAVE_CSV:
			exporter = new SpreadsheetExporter(table);
			filter = new FileNameExtensionFilter("CSV files", "csv");
			chooser.setFileFilter(filter);
			returnVal = chooser.showSaveDialog((Component) e.getSource());
			if(returnVal == JFileChooser.APPROVE_OPTION) {
				exporter.exportToCSV(chooser.getSelectedFile());
			}
			break;
		case NEW:
			GUI.frame.setVisible(false);
			GUI.createAndShowSizeDialog();
			break;
		case EXIT:
			System.exit(0);
			break;
		default:
			System.out.println("Opcao invalida!");
			return;
		}
	}

	public void itemStateChanged(ItemEvent e) {
		System.out.println("item state changed!");
		//...Get information from the item event...
		//...Display it in the text area...
	}

}

enum Events {
	SAVE_FILE(0), OPEN_FILE(1), SAVE_CSV(2), EXIT(3), NEW(4);

	public final int index;
	Events(int index) {
		this.index = index;
	}
}
