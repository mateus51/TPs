package org.neoframework.bookstore.service;

import java.util.List;

import org.neoframework.bookstore.bean.Livrovenda;
import org.neoframework.bookstore.dao.LivrovendaDAO;

import br.com.linkcom.neo.service.GenericService;

public class LivrovendaService extends GenericService<Livrovenda>{
	LivrovendaDAO livrovendaDAO;
	
	public void setLivrovendaDAO(LivrovendaDAO livrovendaDAO) {
		this.livrovendaDAO = livrovendaDAO;
	}

	public List<Livrovenda> maisvendido(){
		return livrovendaDAO.maisvendido();
	}
}
