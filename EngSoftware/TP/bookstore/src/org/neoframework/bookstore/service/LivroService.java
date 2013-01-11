package org.neoframework.bookstore.service;

import java.util.List;

import org.neoframework.bookstore.bean.Livro;
import org.neoframework.bookstore.bean.Livrovenda;
import org.neoframework.bookstore.dao.LivroDAO;

import br.com.linkcom.neo.service.GenericService;

public class LivroService extends GenericService<Livro> {

	protected LivroDAO livroDAO;

	public void setLivroDAO(LivroDAO livroDAO) { this.livroDAO = livroDAO;	}
	

	public List<Livro> maisvendido(){
		return livroDAO.maisvendido();
	}

}
