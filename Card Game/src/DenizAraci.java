
public abstract class DenizAraci extends SavasAraci {

	private String sinif;
	
	public DenizAraci(int seviyePuani, String sinif) {
		super(seviyePuani);
		this.setSinif(sinif);
	}

	public String getSinif() {
		return sinif;
	}

	public void setSinif(String sinif) {
		this.sinif = sinif;
	}
	
		public abstract String getAltSinif();
	    public abstract void setAltSinif(String altSinif);
	
	 	public abstract int getHavaVurusAvantaji();
	    public abstract void setHavaVurusAvantaji(int karaVurusAvantaji);
	    
	    public abstract int getDayaniklilik();
	    public abstract void setDayaniklilik(int dayaniklilik);

	    public abstract int getVurus();
	    public abstract void setVurus(int vurus);

}
