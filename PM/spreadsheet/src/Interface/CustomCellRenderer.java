package Interface;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;

import javax.swing.BorderFactory;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

class CustomCellRenderer extends DefaultTableCellRenderer {
	private static final long serialVersionUID = 1L;
	
	private static final Font defaultFont = new Font("Dialog", Font.PLAIN, 12);
	
	public CustomCellRenderer () {
		super();
		setVerticalAlignment(CENTER);
		setVerticalTextPosition(CENTER);
		setHorizontalAlignment(CENTER);
		setHorizontalTextPosition(CENTER);
	}
	
	// This method is called each time a cell in a column
	// using this renderer needs to be rendered.
	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
		
		// Executa o renderer default
		//super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
		
		// Texto a ser mostrado
		setText(value.toString());
		
		if (column == 0) {
			setBorder(table.getTableHeader().getBorder());
			setBackground(table.getTableHeader().getBackground());
			setFont(table.getTableHeader().getFont());
			setPreferredSize(table.getTableHeader().getSize());
		}
		else {
			setFont(defaultFont);
			if (isSelected) {
				setBorder(BorderFactory.createLineBorder(Color.blue));
				setBackground(Color.cyan);
			}
			else {
				setBorder(null);
				setBackground(Color.white);
			}
		}
		
		return this;
	}

 // The following methods override the defaults for performance reasons
 public void validate() {}
 public void revalidate() {}
 protected void firePropertyChange(String propertyName, Object oldValue, Object newValue) {}
 public void firePropertyChange(String propertyName, boolean oldValue, boolean newValue) {}
}

