package Interface;

import java.awt.Color;
import java.awt.Component;

import javax.swing.AbstractCellEditor;
import javax.swing.BorderFactory;
import javax.swing.JComponent;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.TableCellEditor;

class CustomCellEditor extends AbstractCellEditor implements TableCellEditor {
	private static final long serialVersionUID = 1L;
	
	// This is the component that will handle the editing of the cell value
    JComponent text_field = new JTextField();

    // This method is called when a cell value is edited by the user.
    public Component getTableCellEditorComponent(JTable table, Object obj, boolean isSelected, int row, int column) {
    	
        if (isSelected) {
            ((JTextField)text_field).setText(((CustomTableModel)table.getModel()).getStringAt(row, column));
            ((JTextField)text_field).setBorder(BorderFactory.createLineBorder(Color.red));
            ((JTextField)text_field).setBackground(Color.cyan);
            return text_field;
        }
        return null;
    }

    // This method is called when editing is completed.
    // It must return the new value to be stored in the cell.
    public Object getCellEditorValue() {
    	return ((JTextField)text_field).getText();
    }
}

