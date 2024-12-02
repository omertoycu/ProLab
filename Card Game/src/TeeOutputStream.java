import java.io.OutputStream;
import java.io.IOException;

public class TeeOutputStream extends OutputStream {
    private final OutputStream out1;
    private final OutputStream out2;

    // İki çıkışa yazma işlemi yapacak constructor
    public TeeOutputStream(OutputStream out1, OutputStream out2) {
        this.out1 = out1;
        this.out2 = out2;
    }

    @Override
    public void write(int b) throws IOException {
        out1.write(b); // Konsola yazma
        out2.write(b); // Dosyaya yazma
    }
}
