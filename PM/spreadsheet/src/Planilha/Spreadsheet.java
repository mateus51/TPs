package Planilha;

public class Spreadsheet {
	private Cell[][] cells;
	private int rows, columns;
	
	public Spreadsheet(int rows, int columns) {
		this.rows = rows;
		this.columns = columns;
		this.cells = new Cell[rows][columns];
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				this.cells[i][j] = new Cell(this);
			}
		}
	}
	
	public int numRows() {
		return rows;
	}
	
	public int numColumns() {
		return columns;
	}
	
	public void addObserverToCell(Observer obs, int row, int column) {
		cells[row][column].addObserver(obs);
	}
	
	public void removeObserverFromCell(Observer obs, int row, int column) {
		cells[row][column].removeObserver(obs);
	}
	
	public void observeNobody(Observer obs) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				cells[i][j].removeObserver(obs);
	}
	
	public boolean cellHasExpression(int row, int column) {
		return cells[row][column].hasExpression();
	}
	
	public Double getCellValue(int row, int column) {
		return (cells[row][column]).getVal();
	}
	
	public String getCellString(int row, int column) {
		return (cells[row][column]).getStr();
	}
	
	public void setCellString(int row, int column, String str) {
		cells[row][column].setStr(str);
	}
}
