public abstract class HavaAraci extends SavasAraci{
    private String sinif;

    public HavaAraci(int seviyePuani, String sinif) {
        super(seviyePuani);
        this.sinif = sinif;
    }

    public String getSinif() {
        return sinif;
    }

    public void setSinif(String sinif) {
        this.sinif = sinif;
    }
  
    public abstract int getKaraVurusAvantaji();
    public abstract void setKaraVurusAvantaji(int karaVurusAvantaji);
    
    public abstract String getAltSinif();
    public abstract void setAltSinif(String altSinif);
    
    public abstract int getDayaniklilik();
    public abstract void setDayaniklilik(int dayaniklilik);

    public abstract int getVurus();
    public abstract void setVurus(int vurus);
}
