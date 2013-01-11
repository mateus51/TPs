package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.SequenceGenerator;

import org.neoframework.bookstore.types.Money;

import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_venda", sequenceName="sq_venda")
public class Venda {
	protected Integer idvenda;
	protected Money precototal;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_venda")
	public Integer getIdvenda() {
		return idvenda;
	}
	
	@Required
	public Money getPrecototal() {
		return precototal;
	}
	public void setIdvenda(Integer idvenda) {
		this.idvenda = idvenda;
	}
	public void setPrecototal(Money precototal) {
		this.precototal = precototal;
	}
	
}
