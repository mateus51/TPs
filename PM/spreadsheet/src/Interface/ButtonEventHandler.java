package Interface;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JSpinner;
import javax.swing.JTable;

class ButtonEventHandler implements ActionListener {
	
	JSpinner rows, columns;
	
	ButtonEventHandler(JSpinner rows, JSpinner columns) {
		this.rows = rows;
		this.columns = columns;
	}
	
	public void actionPerformed(ActionEvent e) {
		System.out.println("action performed!\n" + e.getSource().getClass());
		System.out.println("rows: " + rows.getValue());
		System.out.println("cols: " + columns.getValue());
		
		GUI.frame.setVisible(false);
		JTable table = GUI.createJTable(((Integer)rows.getValue()).intValue(), ((Integer)columns.getValue()).intValue());
		GUI.createAndShowGUI(table);
	}
	
}
