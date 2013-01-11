package org.neoframework.bookstore.crud;

import org.neoframework.bookstore.bean.Pessoa;
import org.neoframework.bookstore.filter.PessoaFiltro;

import br.com.linkcom.neo.controller.Controller;
import br.com.linkcom.neo.controller.crud.CrudController;

@Controller(path="/cadastro/pessoa")
public class PessoaCrud extends CrudController<PessoaFiltro, Pessoa, Pessoa> {

}
