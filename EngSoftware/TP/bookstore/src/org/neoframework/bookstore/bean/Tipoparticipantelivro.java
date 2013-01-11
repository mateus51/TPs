package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;

@Entity
@SequenceGenerator(name="sq_tipoparticipantelivro", sequenceName="sq_tipoparticipantelivro")
public class Tipoparticipantelivro {
	protected Integer idtipoparticipantelivro;
	protected String tipoparticipacao;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_tipoparticipantelivro")
	public Integer getIdtipoparticipantelivro() {
		return idtipoparticipantelivro;
	}
	
	@DescriptionProperty
	public String getTipoparticipacao() {
		return tipoparticipacao;
	}
	public void setIdtipoparticipantelivro(Integer idtipoparticipantelivro) {
		this.idtipoparticipantelivro = idtipoparticipantelivro;
	}
	public void setTipoparticipacao(String tipoparticipacao) {
		this.tipoparticipacao = tipoparticipacao;
	}
}
