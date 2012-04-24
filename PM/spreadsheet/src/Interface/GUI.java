package Interface;

import javax.swing.GroupLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.SpinnerNumberModel;
import javax.swing.GroupLayout.Alignment;
import javax.swing.table.TableColumnModel;

import Persistencia.SpreadsheetImporter;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.io.File;

public class GUI {
	
	public static JFrame frame;
    
	public static JTable createJTable(int rows, int columns) {
        JTable table = new JTable(new CustomTableModel(rows, columns));
        
        // Tira auto-resize
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        
        // Desabilita mover colunas
        table.getTableHeader().setReorderingAllowed(false);
        
        // Coloca labels em bold
        table.getTableHeader().setFont(new Font("Dialog", Font.BOLD, 12));
        
        // Seta tamanho e resizable do label de linhas
        table.getColumnModel().getColumn(0).setPreferredWidth(30);
        table.getColumnModel().getColumn(0).setResizable(false);
        
        // Habilita slecionar uma celula
        table.setCellSelectionEnabled(true);
        
        // Adiciona em renderer e um editor p/ cada celula
        TableColumnModel column_model = table.getColumnModel();
        for (int i = 0; i < columns; i++) {
        	column_model.getColumn(i).setCellEditor(new CustomCellEditor());
        	column_model.getColumn(i).setCellRenderer(new CustomCellRenderer());        		
        }
        
        table.setPreferredScrollableViewportSize(new Dimension(705, 160));
        table.setFillsViewportHeight(true);
        
        return table;
	}
	
	private static JMenuBar createMenu(JTable table) {
		
		//Create the menu bar.
		JMenuBar menuBar = new JMenuBar();
		
		//Create the menu
		JMenu menu = new JMenu("Arquivo");
		menu.setMnemonic(KeyEvent.VK_A);
		
		JMenuItem menuItem = new JMenuItem("Novo...");
		menuItem.addActionListener(new MenuEventHandler(null, Events.NEW));
		menu.add(menuItem);
		
		menuItem = new JMenuItem("Abrir...");
		menuItem.addActionListener(new MenuEventHandler(null, Events.OPEN_FILE));
		menu.add(menuItem);
		
		menuItem = new JMenuItem("Salvar...");
		menuItem.addActionListener(new MenuEventHandler(table, Events.SAVE_FILE));
		menu.add(menuItem);
		
		menu.addSeparator();
		
		menuItem = new JMenuItem("Exportar para CSV...");
		menuItem.addActionListener(new MenuEventHandler(table, Events.SAVE_CSV));
		menu.add(menuItem);
		
		menu.addSeparator();
		
		menuItem = new JMenuItem("Sair");
		menuItem.addActionListener(new MenuEventHandler(null, Events.EXIT));
		menu.add(menuItem);

		// Adiciona menu ao menu bar
		menuBar.add(menu);

		return menuBar;
	}
	
	public static void createNewTable(File file) {
		SpreadsheetImporter importer = new SpreadsheetImporter();
		JTable table = importer.openTable(file);
		frame.setVisible(false);
		createAndShowGUI(table);
	}
	
    public static void createAndShowGUI(JTable table) {
        //Create and set up the window.
        frame = new JFrame("Spreadsheet 1.0");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        JPanel panel = new JPanel(new GridLayout(1,0));
        if (table == null)
        	table = createJTable(10, 10);
        panel.add(new JScrollPane(table));
        panel.setOpaque(true); //content panes must be opaque
        frame.setContentPane(panel);
        
        // Create and show menu
        JMenuBar menu = createMenu(table);
        frame.setJMenuBar(menu);
        
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }
    
//    /*    	
    public static void createAndShowSizeDialog() {
        //Create and set up the window.
        frame = new JFrame("Spreadsheet 1.0");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        // Creates JPanel
        JPanel panel = new JPanel();
        GroupLayout layout = new GroupLayout(panel);
        panel.setLayout(layout);
        
        // Turn on automatically adding gaps between components
        layout.setAutoCreateGaps(true);
        
        // Turn on automatically creating gaps between components that touch
        // the edge of the container and the container.
        layout.setAutoCreateContainerGaps(true);
        
        // Creates labels
        JLabel label1 = new JLabel("# linhas: ");
        JLabel label2 = new JLabel("# colunas: ");
        
        // Spinner 1
        SpinnerNumberModel rowsModel = new SpinnerNumberModel(10, 1, 1000, 1);
        JSpinner spinner1 = new JSpinner(rowsModel);
        
        // Spinner 2
        SpinnerNumberModel colsModel = new SpinnerNumberModel(10, 1, 26, 1);
        JSpinner spinner2 = new JSpinner(colsModel);
        
        // Botao OK
        JButton button = new JButton("OK");
        button.addActionListener(new ButtonEventHandler(spinner1, spinner2));
        
        // Create a sequential group for the horizontal axis.
        GroupLayout.SequentialGroup hGroup = layout.createSequentialGroup();
        
        // The sequential group in turn contains two parallel groups.
        // One parallel group contains the labels, the other the text fields.
        // Putting the labels in a parallel group along the horizontal axis
        // positions them at the same x location.
        hGroup.addGroup(layout.createParallelGroup().addComponent(label1).addComponent(label2).addComponent(button));
        hGroup.addGroup(layout.createParallelGroup().addComponent(spinner1).addComponent(spinner2));
        layout.setHorizontalGroup(hGroup);
        
        // Create a sequential group for the vertical axis.
        GroupLayout.SequentialGroup vGroup = layout.createSequentialGroup();
        
        // The sequential group contains two parallel groups that align
        // the contents along the baseline. The first parallel group contains
        // the first label and text field, and the second parallel group contains
        // the second label and text field. By using a sequential group
        // the labels and text fields are positioned vertically after one another.
        vGroup.addGroup(layout.createParallelGroup(Alignment.BASELINE).addComponent(label1).addComponent(spinner1));
        vGroup.addGroup(layout.createParallelGroup(Alignment.BASELINE).addComponent(label2).addComponent(spinner2));
        vGroup.addGroup(layout.createParallelGroup(Alignment.CENTER).addComponent(button));
        layout.setVerticalGroup(vGroup);
        
        //Display the window.
        panel.setOpaque(true); //content panes must be opaque
        frame.setContentPane(panel);
        frame.pack();
        frame.setVisible(true);
    }
//     */        
	
}
