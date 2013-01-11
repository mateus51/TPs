package org.neoframework.bookstore.bean;

import java.sql.Timestamp;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.SequenceGenerator;
import javax.persistence.Transient;

import org.neoframework.bookstore.types.File;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;
import br.com.linkcom.neo.bean.annotation.DisplayName;
import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_arquivo", sequenceName="sq_arquivo")
public class Arquivo implements File {
	protected Long idarquivo;
	protected String nome;
	protected String tipoconteudo;
	protected Long tamanho;
	protected byte[] content;
	
	

	@Id
	@DisplayName("Id")
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_arquivo")
	public Long getIdarquivo() {
		return idarquivo;
	}
	public void setIdarquivo(Long id) {
		this.idarquivo = id;
	}

	
	@Required
	@MaxLength(500)
	@DescriptionProperty
	public String getNome() {
		return nome;
	}
	
	@Required
	@MaxLength(50)
	public String getTipoconteudo() {
		return tipoconteudo;
	}
	
	public Long getTamanho() {
		return tamanho;
	}
	

	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public void setTipoconteudo(String tipoconteudo) {
		this.tipoconteudo = tipoconteudo;
	}
	
	public void setTamanho(Long tamanho) {
		this.tamanho = tamanho;
	}
	
	
	@Transient
	public byte[] getContent() {
		return this.content;
	}

	@Transient
	public String getName() {
		return getNome();
	}

	@Transient
	public Long getCdfile() {
		if(getIdarquivo() == null){
			return null;
		}
		return new Long(getIdarquivo().intValue());
	}

	@Transient
	public String getContenttype() {
		return getTipoconteudo();
	}

	@Transient
	public Long getSize() {
		return getTamanho();
	}

	@Transient
	public Timestamp getTsmodification() {
		return new Timestamp(0);
	}

	public void setContenttype(String contenttype) {
		setTipoconteudo(contenttype);
	}

	public void setContent(byte[] content) {
		this.content = content;
	}

	public void setCdfile(Long cdfile) {
		setIdarquivo(cdfile);
	}

	public void setName(String name) {
		setNome(name);
	}

	public void setSize(Long size) {
		setTamanho(size);
	}

	public void setTsmodification(Timestamp tsmodification) {
		
	}
}
