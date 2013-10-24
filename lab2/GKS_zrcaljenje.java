
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKS_zrcaljenje extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, -10, 10, -5, 5, getWidth(), getHeight());
    double step = 0.01;

    int k = 3;
    int l = 6;
    double alfa = Math.toDegrees(Math.atan(k));
    System.out.println(alfa);
    MT2D mt1 = new MT2D();
    MT2D mt2 = new MT2D();
    gks.postaviBoju(Color.red);
    pravac(gks);
    gks.postaviBoju(Color.black);
    lik(gks, mt1);
    mt1.pomakni(0, -l);
    mt2.rotiraj(-alfa);
    mt2.mult(mt1);
    mt1.zrcaliNaX();
    mt1.mult(mt2);
    mt2.rotiraj(alfa);
    mt2.mult(mt1);
    mt1.pomakni(0, l);
    mt1.mult(mt2);
    gks.trans(mt1);
    gks.postaviBoju(Color.blue);
    lik(gks, mt1);
  }

  public void lik(GKS gks, MT2D lmt) {
    MT2D m1 = new MT2D();
    gks.postaviNa(0, 0.5);
    gks.linijaDo(3, 0.5);
    gks.postaviNa(0, 0.5);
    gks.linijaDo(0, 3);
    gks.linijaDo(0.35, 2.70);
    gks.postaviNa(0,3);
    gks.linijaDo(-0.25, 3.30);
    gks.postaviNa(2.8, 0.5);
    gks.linijaDo(2.8, 2.0);
    gks.linijaDo(2.4, 2.0);
    gks.linijaDo(2.4, 2.2);
    gks.linijaDo(3.2, 2.2);
    gks.linijaDo(3.2, 2.0);
    gks.linijaDo(2.8, 2.0);
    elipse(gks, 0.5, 0.5, 0.01);
    elipse(gks, 0.25, 0.25, 0.01);
    m1.pomakni(3, 0);
    lmt.mult(m1);
    gks.trans(lmt);
    elipse(gks, 0.5, 0.5, 0.01);
    elipse(gks, 0.25, 0.25, 0.01);
  }

  public void pravac(GKS gks) {
    double i;
    gks.postaviNa(-5, -5*3 + 6);
    for (i = -5; i < 5; i+= 0.01) {
      double c = i*3 + 6;
      gks.linijaDo(i, c);
    }
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