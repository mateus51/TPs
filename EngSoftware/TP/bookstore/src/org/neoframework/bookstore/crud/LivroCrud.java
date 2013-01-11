package org.neoframework.bookstore.crud;

import java.util.List;

import org.neoframework.bookstore.bean.Livro;
import org.neoframework.bookstore.bean.Livrovenda;
import org.neoframework.bookstore.filter.LivroFiltro;
import org.neoframework.bookstore.service.LivroService;
import org.neoframework.bookstore.service.LivrovendaService;
import org.springframework.web.servlet.ModelAndView;

import br.com.linkcom.neo.controller.Action;
import br.com.linkcom.neo.controller.Controller;
import br.com.linkcom.neo.controller.DefaultAction;
import br.com.linkcom.neo.controller.crud.CrudController;
import br.com.linkcom.neo.core.web.WebRequestContext;

@Controller(path="/busca/livro")
public class LivroCrud extends CrudController<LivroFiltro, Livro, Livro> {
	LivrovendaService livrovendaService = new LivrovendaService();
	LivroService livroService = new LivroService();
	
	public void setLivrovendaService(LivrovendaService livrovendaService) {
		this.livrovendaService = livrovendaService;
	}
	
	
	public void setLivroService(LivroService livroService) {
		this.livroService = livroService;
	}


	@Action("topvendas")
	public ModelAndView livroTopVendas(WebRequestContext request){
		
		List<Livrovenda> lista = livrovendaService.maisvendido();
		Livrovenda livrovenda = new Livrovenda();
		livrovenda.setLivrovendatrans(lista);
		
		return new ModelAndView("/crud/livrotop").addObject("lista", livrovenda);
	}
	@Action("topcriticas")
	public ModelAndView livroTopCriticas(WebRequestContext request){
		
		
		return new ModelAndView("livroTop");
	}
	@Action("topnoticias")
	public ModelAndView livroTopNoticias(WebRequestContext request){
	
	
	return new ModelAndView("livroTop");
}
}
