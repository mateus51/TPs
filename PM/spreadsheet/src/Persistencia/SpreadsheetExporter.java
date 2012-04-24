package Persistencia;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JTable;

import Interface.CustomTableModel;

public class SpreadsheetExporter {

	private JTable table;
	
	public SpreadsheetExporter(JTable table) {
		this.table = table;
	}
	
	public void saveToFile(File file) {
		FileWriter fw;
		try {
			fw = new FileWriter(file);
		} catch (IOException e) {
			System.out.println("Erro ao criar arquivo!\n" + e.getMessage());
			return;
		}
		
		String value;
		String[] tokens;
		
		try {
			fw.write(table.getModel().getRowCount() + System.getProperty("line.separator"));
			fw.write(table.getModel().getColumnCount() + System.getProperty("line.separator"));
			for (int i = 0; i < table.getRowCount(); i++) {
				for (int j = 1; j < table.getColumnCount(); j++) {
					value = ((CustomTableModel) table.getModel()).getStringAt(i, j);
					if (value.contains(";")) {
						tokens = value.split(";");
						for (int k = 0; k < tokens.length - 1; k++) {
							fw.write(tokens[k]);
							fw.write("\";\"");
						}
						fw.write(tokens[tokens.length - 1]);
					}
					else {
						fw.write(value);
					}
					fw.write("; ");
				}
				fw.write(System.getProperty("line.separator"));
			}
		} catch (IOException e) {
			System.out.println("Erro ao escrever no arquivo!\n" + e.getMessage());
			return;
		}
		
		try {
			fw.close();
		} catch (IOException e) {
			System.out.println("Erro ao fechar arquivo!\n" + e.getMessage());
		}
	}
	
	public void exportToCSV(File file) {
		FileWriter fw;
		try {
			fw = new FileWriter(file);
		} catch (IOException e) {
			System.out.println("Erro ao criar arquivo!\n" + e.getMessage());
			return;
		}
		
		try {
			for (int i = 0; i < table.getRowCount(); i++) {
				for (int j = 1; j < table.getColumnCount(); j++) {
					fw.write(table.getModel().getValueAt(i, j).toString());
					fw.write(",");
				}
				fw.write(System.getProperty("line.separator"));
			}
		} catch (IOException e) {
			System.out.println("Erro ao escrever no arquivo!\n" + e.getMessage());
			return;
		}
		
		try {
			fw.close();
		} catch (IOException e) {
			System.out.println("Erro ao fechar arquivo!\n" + e.getMessage());
		}
	}
	
}
