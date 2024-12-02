public class Siha extends HavaAraci {

    private int dayaniklilik;
    private int vurus;
    private int karaVurusAvantaji; 
    private int denizVurusAvantaji;
    private String altSinif;

    public Siha(int dayaniklilik, int seviyePuani, String sinif, int vurus, int karaVurusAvantaji, int denizVurusAvantaji, String altSinif) {
        super(seviyePuani, sinif);
        this.dayaniklilik = dayaniklilik;
        this.vurus = vurus;
        this.karaVurusAvantaji = karaVurusAvantaji;
        this.denizVurusAvantaji = denizVurusAvantaji;
        this.altSinif = altSinif;
    }

    @Override 
    public String getAltSinif()
    {
    	return altSinif;
    }
    @Override
    public void setAltSinif(String altSinif)
    {
    	this.altSinif = altSinif;
    }
    
    @Override
    public int getDayaniklilik() {
        return dayaniklilik;
    }
    @Override
   public void setDayaniklilik(int dayaniklilik) {
        if (dayaniklilik < 0) {
            this.dayaniklilik = 0;
        }
        else{
            this.dayaniklilik = dayaniklilik;
            }
        }
        
    @Override
    public int getVurus() {
        return vurus;
    }
    @Override
    public void setVurus(int vurus) {
        this.vurus = vurus;
    }
    
    @Override
    public int getKaraVurusAvantaji() {
        return karaVurusAvantaji;
    }
    @Override
    public void setKaraVurusAvantaji(int karaVurusAvantaji) {
        this.karaVurusAvantaji = karaVurusAvantaji;
    }
    
    public int getDenizVurusAvantaji()
    {
    	return denizVurusAvantaji;
    }

   public void setDenizVurusAvantaji(int denizVurusAvantaji)
   {
	   this.denizVurusAvantaji = denizVurusAvantaji;
   }
   
   @Override
   public void DurumGuncelle(int vurus) {
       // Dayanıklılığı saldırı değeri kadar azaltıyoruz
       this.dayaniklilik -= vurus;
       if (dayaniklilik < 0) {
           dayaniklilik = 0; // Dayanıklılık 0'ın altına düşmesin
       }

       // Seviye puanını güncelle
       if (vurus > 10) {
           this.setSeviyePuani(this.getSeviyePuani() + 1); // Basit bir güncelleme mantığı
       }
       
       System.out.println("Güncellenmiş Dayanıklılık: " + dayaniklilik + ", Seviye Puanı: " + getSeviyePuani());
   }
}
