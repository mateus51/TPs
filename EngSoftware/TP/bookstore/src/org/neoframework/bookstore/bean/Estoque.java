package org.neoframework.bookstore.bean;

import java.math.BigInteger;
import java.sql.Date;

import javax.persistence.Entity;
import javax.persistence.Id;

@Entity
public class Estoque {
	protected Integer idlivro;
	protected BigInteger quantidade;
	protected Date dtultimaremessa;
	protected Date dtprevisao;
	
	@Id
	public Integer getIdlivro() {
		return idlivro;
	}
	public BigInteger getQuantidade() {
		return quantidade;
	}
	public Date getDtultimaremessa() {
		return dtultimaremessa;
	}
	public Date getDtprevisao() {
		return dtprevisao;
	}
	public void setIdlivro(Integer idlivro) {
		this.idlivro = idlivro;
	}
	public void setQuantidade(BigInteger quantidade) {
		this.quantidade = quantidade;
	}
	public void setDtultimaremessa(Date dtultimaremessa) {
		this.dtultimaremessa = dtultimaremessa;
	}
	public void setDtprevisao(Date dtprevisao) {
		this.dtprevisao = dtprevisao;
	}
}
