package Planilha;

class Cell extends Subject implements Observer {
	private String str = "";
	private Double val = null;
	private boolean has_exp = false;
	private Spreadsheet spreadsheet = null;
	
	Cell(Spreadsheet s) {
		spreadsheet = s;
	}
	
	public String getStr() {
		return str;
	}
	
	public Spreadsheet getSpreadsheet() {
		return spreadsheet;
	}
	
	public void setStr(String str) {
		this.str = str;
		if (!str.isEmpty() && str.startsWith("=")) {
			has_exp = true;
		}
		else {
			has_exp = false;
		}
		this.val = null;
		notifyObservers();
	}
	
	public boolean hasExpression() {
		return has_exp;
	}
	
	public Double getVal() {
		if (has_exp) {
			if (val == null)
				val = Expression.postfixEvaluate(this);
			return val;
		}
		try {
			return new Double(str);
		}
		catch(NumberFormatException e) {
			System.out.println("catched exception!");
			return new Double(0);
		}
	}
	
	public void observe(int row, int column) {
		this.spreadsheet.addObserverToCell(this, row, column);
	}
	
	public void observeNobody() {
		this.spreadsheet.observeNobody(this);
	}
	
	public void update(Subject s) {
		val = null;
		notifyObservers();
	}
}
