
public abstract class KaraAraci extends SavasAraci{

	public String sinif;
	
	public KaraAraci(int seviyePuani , String sinif) {
		super(seviyePuani);
		this.sinif = sinif;
	}
	
	  public String getSinif() {
	        return sinif;
	    }

	    public void setSinif(String sinif) {
	        this.sinif = sinif;
	    }
	    
	    public abstract String getAltSinif();
	    public abstract void setAltSinif(String altSinif);
	    
	    public abstract int getDenizVurusAvantaji();
	    public abstract void setDenizVurusAvantaji(int denizVurusAvantaji);
	    
	    public abstract int getDayaniklilik();
	    public abstract void setDayaniklilik(int dayaniklilik);

	    public abstract int getVurus();
	    public abstract void setVurus(int vurus);
	    
}
