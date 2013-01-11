package org.neoframework.bookstore;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Date;
import java.util.Calendar;
import java.util.List;
import java.util.Set;

import org.neoframework.bookstore.bean.Tipoparticipantelivro;
import org.neoframework.bookstore.dao.TipoparticipantelivroDAO;
import org.neoframework.bookstore.types.Money;
import org.springframework.web.servlet.ModelAndView;

import br.com.linkcom.neo.controller.Controller;
import br.com.linkcom.neo.controller.DefaultAction;
import br.com.linkcom.neo.controller.MultiActionController;
import br.com.linkcom.neo.core.web.WebRequestContext;
import br.com.linkcom.neo.types.ListSet;

@Controller(path="/teste/HelloWorld")
@SuppressWarnings("unused")
public class HelloWorldController extends MultiActionController{

	@DefaultAction
	public ModelAndView action(WebRequestContext request){
		
		
		return new ModelAndView("hello");
	}
	private String setListaPessoa(){
		StringBuilder sb = leitura("c:\\pessoa.txt",Boolean.TRUE);
		String[] nome = sb.toString().split("\n");
		sb = new StringBuilder();
		for(int i=0; i<nome.length; i++){
			sb.append("INSERT INTO public.pessoa (\nidpessoa,\nnome,\ndtnascimento\n)\nVALUES (\n");
			sb.append(i+1+",\n");
			nome[i] = nome[i].replaceAll("'","`");
			sb.append("'"+nome[i]+"',\n");
			
			Calendar dtLimiteAux = Calendar.getInstance();
			dtLimiteAux.set(1930, 1, 1);
			dtLimiteAux.add(Calendar.YEAR, new Double(60*Math.random()).intValue());
			dtLimiteAux.add(Calendar.MONTH, new Double(11*Math.random()).intValue());
			dtLimiteAux.add(Calendar.DAY_OF_MONTH, new Double(28*Math.random()).intValue());
			Date data = new Date(dtLimiteAux.getTimeInMillis());
			
			sb.append("'"+data+"'\n);\n\n");
			
			
		}
		escrita(sb.toString(),"c:\\sqlpessoa.sql");
		return "Lista de pessoas gerada!<BR>(sqlpessoa.sql)";
	}
	
	private String setListaLivro(){
		
		StringBuilder sb = leitura("c:\\livro.txt",Boolean.FALSE);
		
		String[] nome = sb.toString().replaceAll("          ", "").split("\\.");
		Set<String> titulo = new ListSet<String>(String.class);
		String[] t;
		for(int j = 0; j<nome.length; j++){
			t = nome[j].split(",");
			for(int k=0; k<t.length;k++ ){
				if(!titulo.contains(t[k])){
					titulo.add(t[k]);
				}
			}
				
		}
		
		sb = new StringBuilder();
		Double d;
		Money m;
		int i = 0;
		for(String s : titulo){
			sb.append("INSERT INTO public.livro (\nidlivro,\ntitulo,\nlancamento,\ngenero,\npreco,\nanolancamento,\nedicao\n)\nVALUES (\n");
			sb.append((++i)+",\n");
			
			
			if(s.startsWith(" ")){
				s = s.replaceFirst(" ", "");
			}
			sb.append("'"+s+"',\n");
			
			if(100*Math.random() > 70){
				sb.append("true"+",\n");
			}
			else{
				sb.append("false"+",\n");
			}
			d = 1+30*Math.random();
			sb.append(d.intValue()+",\n");
			
			
			m = new Money(30+170*Math.random());
		
			sb.append("'"+m+"',\n");
			
			d=(2000+12*Math.random());
			sb.append(d.intValue()+",\n");
			
			d=(1+20*Math.random());
			sb.append(d.intValue()+"\n);\n");
			
			//insert estoque
			sb.append("INSERT INTO public.estoque (\nidlivro,\nquantidade,\ndtultimaremessa,\ndtprevisao\n)\nVALUES (\n");
			sb.append(i+",\n");
			
			d= 100*Math.random();
			if(d < 10 && d > 3 )
				d = 0.0;
			sb.append(d.intValue()+",\n");
			
			Date data = new java.sql.Date(System.currentTimeMillis());
			sb.append("'"+data.toString()+"',\n");
			
			d = 100*Math.random();
			if(d>70){
			Calendar dtLimiteAux = Calendar.getInstance();
			dtLimiteAux.setTimeInMillis(data.getTime());
			dtLimiteAux.add(Calendar.DAY_OF_MONTH, d.intValue());
			
			data = new Date(dtLimiteAux.getTimeInMillis());
			sb.append("'"+data+"'");
			}
			else
				sb.append("null");
			sb.append("\n);\n\n");
			
		}
		escrita(sb.toString(),"c:\\sqllivro.sql");
		return "Lista de livros gerada!<BR>(sqllivro.sql)";
	}
	private void escrita(String texto, String path){
		 File arquivo = new File(path);
         FileOutputStream fos;
		try {
			fos = new FileOutputStream(arquivo);
	         fos.write(texto.getBytes());
	         fos.close(); 
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
	private StringBuilder leitura(String path, Boolean barraN){
		StringBuilder sb = new StringBuilder();
		try {
		        BufferedReader in = new BufferedReader(new FileReader(path));
		            String str;
		            while (in.ready()) {
		                str = in.readLine();
		                if(barraN)
		                	sb.append(str+"\n");
		                else
		                	sb.append(str);
		            }
		            in.close();
		} catch (IOException e) {
	    }
		return sb;
	}
}
