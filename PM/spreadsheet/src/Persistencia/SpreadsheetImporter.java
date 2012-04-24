package Persistencia;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import javax.swing.JTable;

import Interface.GUI;

public class SpreadsheetImporter {
	
	public JTable openTable(File file) {
		JTable table;
		BufferedReader br;
		try {
			br = new BufferedReader(new FileReader(file));
		} catch (FileNotFoundException e1) {
			System.out.println("Arquivo não encontrado!");
			return null;
		}
		
		try {
			int rows = (new Integer(br.readLine())).intValue();
			int columns = (new Integer(br.readLine())).intValue();
			
			table = GUI.createJTable(rows, columns);
			String[] cells, tokens;
			String value;

			for (int i = 0; (value = br.readLine()) != null; i++) {
				cells = value.split("; ");
				for (int j = 0; j < cells.length; j++) {
					if (cells[j].contains("\";\"")) {
						tokens = cells[j].split("\";\"");
						cells[j] = new String();
						for (int k = 0; k < tokens.length - 1; k++) {
							cells[j] = cells[j].concat(tokens[k] + ";");
						}
						cells[j] = cells[j].concat(tokens[tokens.length - 1]);
					}
					table.getModel().setValueAt(cells[j], i, j + 1);
				}
			}
		} catch (IOException e) {
			System.out.println("Erro ao escrever no arquivo!\n" + e.getMessage());
			return null;
		}
		
		try {
			br.close();
		} catch (IOException e) {
			System.out.println("Erro ao fechar arquivo!\n" + e.getMessage());
		}
		
		return table;
	}
}
