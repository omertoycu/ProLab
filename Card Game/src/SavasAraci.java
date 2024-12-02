public abstract class SavasAraci implements Cloneable{
    private int seviyePuani;

    public SavasAraci(int seviyePuani) {
        this.seviyePuani = seviyePuani;
    }

    public abstract int getDayaniklilik();
    public abstract void setDayaniklilik(int dayaniklilik);

    public abstract String getSinif();
    public abstract void setSinif(String sinif);

    public abstract int getVurus();
    public abstract void setVurus(int vurus);

    public int getSeviyePuani() {
        return seviyePuani;
    }

    public void setSeviyePuani(int seviyePuani) {
        this.seviyePuani = seviyePuani;
    }
    public void kartPuaniGoster() {
        System.out.println("Dayan�kl�l�k: " + getDayaniklilik() + ", Seviye Puan�: " + seviyePuani );
    }

    @Override
    public SavasAraci clone() {
        try {
            return (SavasAraci) super.clone();
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
            return null; // Eğer klonlama başarısız olursa
        }
    }
    public abstract void DurumGuncelle(int vurus);

}
