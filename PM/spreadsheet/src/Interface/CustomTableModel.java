package Interface;

import javax.swing.table.AbstractTableModel;
import Planilha.*;

public class CustomTableModel extends AbstractTableModel {
	private static final long serialVersionUID = 1L;
	
	private String[] columnNames = {"", "A", "B", "C", "D", "E", "F", "G", "H", "I",
									"J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
									"T", "U", "V", "W", "X", "Y", "Z"};
    private Spreadsheet spreadsheet;
    private boolean DEBUG = false;

    
    public CustomTableModel(int rows, int columns) {
    	spreadsheet = new Spreadsheet(rows, columns);
    	setRowNames();
    }

    public int getColumnCount() {
        return spreadsheet.numColumns();
    }

    public int getRowCount() {
        return spreadsheet.numRows();
    }

    public String getColumnName(int col) {
        return columnNames[col];
    }

    public Object getValueAt(int row, int col) {
    	if (spreadsheet.cellHasExpression(row, col))
    		return spreadsheet.getCellValue(row, col);
    	else
    		return spreadsheet.getCellString(row, col);
    }
    
    public String getStringAt(int row, int column) {
    	return spreadsheet.getCellString(row, column);
    }

    /*
     * JTable uses this method to determine the default renderer/
     * editor for each cell.  If we didn't implement this method,
     * then the last column would contain text ("true"/"false"),
     * rather than a check box.
     *
    public Class<?> getColumnClass(int c) {
        return getValueAt(0, c).getClass();
    }*/

    /*
     * Don't need to implement this method unless your table's
     * editable.
     */
    public boolean isCellEditable(int row, int col) {
    	return (col > 0);
    }

    public void setValueAt(Object obj, int row, int col) {
        if (DEBUG) {
            System.out.println("Setting value at " + row + "," + col + " to " + obj);
        }

        spreadsheet.setCellString(row, col, (String) obj);
        fireTableDataChanged();

        if (DEBUG) {
            System.out.println("New value of data:");
            printDebugData();
        }
    }

    private void setRowNames() {
    	int num_rows = spreadsheet.numRows();
    	for(int i = 0; i < num_rows; i++) {
    		spreadsheet.setCellString(i, 0, Integer.toString(i+1));
    	}
    }
    
    private void printDebugData() {
        int numRows = getRowCount();
        int numCols = getColumnCount();

        for (int i=0; i < numRows; i++) {
            System.out.print("    row " + i + ":");
            for (int j=0; j < numCols; j++) {
                System.out.print("  " + spreadsheet.getCellString(i, j));
            }
            System.out.println();
        }
        System.out.println("--------------------------");
    }
}