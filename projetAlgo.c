

Define NombreDePoints 10



point TabPoints[NombreDePoints];

point p0 = CreerPoints(0,0);
TabPoints[0] = p0;
point p1 = CreerPoints(4,5);
TabPoints[1] = p1;
point p2 = CreerPoints(2,4);
TabPoints[2] = p2;


//Indice --> point actuel
int ProchainPoint(point p0, int indice){
  double DProchainPoint = LongeurEntre2Points(p0,TabPoints[++indice]);
  int indiceDuPlusCourt = indice;

  for(; indice<NombreDePoints-2;indice++){
    double plusProche = LongeurEntre2Points(p0,TabPoints[indice+1]);
    
    if (plusProche < DProchainPoint){
      DProchainPoint = PlusProche;
      indiceDuPlusCourt = indice;
    }
  }
  return indiceDuPlusCourt;
}
