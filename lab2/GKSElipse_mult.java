
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKSElipse_mult extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, -10, 10, -5, 5, getWidth(), getHeight());
    gks.postaviBoju(Color.black);
    double step = 0.01;
    // draw axis
    gks.postaviNa(-10, 0);
    gks.linijaDo(10, 0);
    gks.postaviNa(0, 5);
    gks.linijaDo(0, -5);
    
    MT2D mt1 = new MT2D();
    MT2D mt2 = new MT2D();

    gks.postaviBoju(Color.red);
    mt2.pomakni(4.0, 0.0);
    mt1.rotiraj(-30.0);
    mt2.mult(mt1);
    gks.trans(mt2);
    elipse(gks, 6.0, 3.0, step);
    
    // elipsa pomaknuta za (4, 0) pa zarotirana za -30 stupnjeva
    gks.postaviBoju(Color.blue);
    mt2.rotiraj(-30.0);
    mt1.pomakni(4.0, 0.0);
    mt2.mult(mt1);
    gks.trans(mt2);
    elipse(gks, 6.0, 3.0, step);

    // elipsa rotirana za 75 stupnjeva, pomaknuta za 3 u desno, zrcaljena na osi y
    gks.postaviBoju(Color.green);
    mt2.zrcaliNaY();
    mt1.pomakni(3.0, 0.0);
    mt2.mult(mt1);
    mt1.rotiraj(75.0); 
    mt2.mult(mt1);
    gks.trans(mt2);
    elipse(gks, 4.0, 1.0, step);
    
  }

  public void elipse(GKS gks, double a, double b, double step) {
    double phi;
    double x, y;
    gks.postaviNa(a * Math.cos(0), b * Math.sin(0));
    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
      x = a * Math.cos(phi);
      y = b * Math.sin(phi);
      gks.linijaDo(x, y);
    }
  }
}