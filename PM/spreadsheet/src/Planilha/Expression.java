package Planilha;

import java.util.*;

class Expression {

	static Double postfixEvaluate(Cell cell) {
		cell.observeNobody();
		
		Stack<Double> stack = new Stack<Double>();
		String[] tokens = cell.getStr().substring(1).split(" ");
		
		Double n1, n2;
		int row, column;
		
		for (int i = 0; i < tokens.length; i++) {
			
			if (!tokens[i].isEmpty()) {
				
				if (tokens[i].startsWith("SUM(")) {
					stack.push(evaluateSUM(tokens[i].substring(4, tokens[i].length() - 1), cell));
				}
				
				else if (tokens[i].startsWith("AVG(")) {
					stack.push(evaluateAVG(tokens[i].substring(4, tokens[i].length() - 1), cell));
				}
				
				else if (tokens[i].compareTo("+") == 0) {
					n2 = stack.pop();
					n1 = stack.pop();
					stack.push(new Double(n1.doubleValue() + n2.doubleValue()));
				}
				
				else if (tokens[i].compareTo("-") == 0) {
					n2 = stack.pop();
					n1 = stack.pop();
					stack.push(new Double(n1.doubleValue() - n2.doubleValue()));
				}
				
				else if (tokens[i].compareTo("*") == 0) {
					n2 = stack.pop();
					n1 = stack.pop();
					stack.push(new Double(n1.doubleValue() * n2.doubleValue()));
				}
				
				else if (tokens[i].compareTo("/") == 0) {
					n2 = stack.pop();
					n1 = stack.pop();
					stack.push(new Double(n1.doubleValue() / n2.doubleValue()));
				}
				
				// É uma referência a uma célula
				else if (tokens[i].matches("[A-Z][0-9]+")) {
					row = (new Integer(tokens[i].substring(1))).intValue() - 1;
					column = SpreadsheetIndex.valueOf(tokens[i].substring(0, 1)).index;
					cell.observe(row, column);
					stack.push(cell.getSpreadsheet().getCellValue(row, column));
					
					System.out.println("pushed: " + tokens[i] + "[" + row + "][" + column + "] " + cell.getSpreadsheet().getCellValue(row, column));
				}
				
				// É um número
				else {
					stack.push(new Double(tokens[i]));
				}				
			}
		}
		return stack.pop();
	}
	
	private static Double evaluateSUM(String params, Cell cell) {
		int start_column, end_column, start_row, end_row;
		String[] cells = params.split(":");
		double result = 0;

		start_row = (new Integer(cells[0].substring(1))).intValue() - 1;
		start_column = SpreadsheetIndex.valueOf(cells[0].substring(0, 1)).index;
		end_row = (new Integer(cells[1].substring(1))).intValue() - 1;
		end_column = SpreadsheetIndex.valueOf(cells[1].substring(0, 1)).index;
		
		if (start_column < end_column) {
			for (int i = start_column; i <= end_column; i++) {
				result += cell.getSpreadsheet().getCellValue(start_row, i).doubleValue();
				cell.observe(start_row, i);
			}
		}
		else if (start_row < end_row) {
			for (int i = start_row; i <= end_row; i++) {
				result += cell.getSpreadsheet().getCellValue(i, start_column).doubleValue();
				cell.observe(i, start_column);
			}
		}
		else {
			cell.observe(start_row, start_column);
			return cell.getSpreadsheet().getCellValue(start_row, start_column);
		}
		return new Double(result);
	}
	
	private static Double evaluateAVG(String params, Cell cell) {
		int start_column, end_column, start_row, end_row;
		int total_celulas = 0;
		String[] cells = params.split(":");
		double result = 0;

		start_row = (new Integer(cells[0].substring(1))).intValue() - 1;
		start_column = SpreadsheetIndex.valueOf(cells[0].substring(0, 1)).index;
		end_row = (new Integer(cells[1].substring(1))).intValue() - 1;
		end_column = SpreadsheetIndex.valueOf(cells[1].substring(0, 1)).index;
		
		if (start_column < end_column) {
			for (int i = start_column; i <= end_column; i++) {
				result += cell.getSpreadsheet().getCellValue(start_row, i).doubleValue();
				cell.observe(start_row, i);
				total_celulas++;
			}
		}
		else if (start_row < end_row) {
			for (int i = start_row; i <= end_row; i++) {
				result += cell.getSpreadsheet().getCellValue(i, start_column).doubleValue();
				cell.observe(i, start_column);
				total_celulas++;
			}
		}
		else {
			cell.observe(start_row, start_column);
			return cell.getSpreadsheet().getCellValue(start_row, start_column);
		}
		return new Double(result/total_celulas);
	}
}

enum SpreadsheetIndex {
	A(0),  B(1),  C(2),  D(3),  E(4),  F(5),
	G(6),  H(7),  I(8),  J(9),  K(10), L(11),
	M(12), N(13), O(14), P(15), Q(16), R(17),
	S(18), T(19), U(20), V(21), W(22), X(23),
	Y(24), Z(25);

    public final int index;
    SpreadsheetIndex(int index) {
        this.index = index + 1;
    }
}

