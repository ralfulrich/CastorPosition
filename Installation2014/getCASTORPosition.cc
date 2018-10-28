void getCASTORPosition() {


// *****************************************
// ALL NUMBERS ARE IN MILLIMETER !!! *******
// *****************************************



// *****************************************
// DEFINE CONSTANTS ETC ********************
// *****************************************

	const double castor_inner_octant_radius = 44;//40.6507;

	const double beampipe_r = (57+0.5)/2;
	const double maxOpening = 10.;
	const double pi = TMath::Pi();

	// maximum expected shift of CASTOR
	const double maxShift_IPnear_Yup = 4.;
	const double maxShift_IPfar_Yup = 4.;
	const double maxShift_nonIPnear_Yup = 4.;
	const double maxShift_nonIPfar_Yup = 4.;

	const double maxShift_IPnear_Ydown = 1.;
	const double maxShift_IPfar_Ydown = 1.;
	const double maxShift_nonIPnear_Ydown = 1.;
	const double maxShift_nonIPfar_Ydown = 1.;

	const double maxShift_IPnear_Xout = 4.;
	const double maxShift_IPfar_Xout = 4.;
	const double maxShift_nonIPnear_Xout = 4.;
	const double maxShift_nonIPfar_Xout = 4.;

	const double maxShift_IPnear_Xin = 4.;
	const double maxShift_IPfar_Xin = 4.;
	const double maxShift_nonIPnear_Xin = 4.;
	const double maxShift_nonIPfar_Xin = 4.;

// *****************************************
// Enter here the IR sensor data !!! *******
// *****************************************

	const double IPnearTOP_Dist = 25.;

	const double IPnearBOT_Dist = 25.;
	
	const double IPfarTOP_Dist = 7.;

	const double IPfarBOT_Dist = 8.;
	
	const double nonIPnearTOP_Dist = 14.;

	const double nonIPnearMID_Dist = 20.;

	const double nonIPnearBOT_Dist = 14.;
	
	const double nonIPfarTOP_Dist = 14.;

	const double nonIPfarMID_Dist = 26.;

	const double nonIPfarBOT_Dist = 22.;


// *****************************************
// *****************************************

	TCanvas* c1 = new TCanvas("c1","c1",750,750);
	c1->Divide(2,2);

	TLegend* legIPfar = new TLegend(0.53,0.7,0.9,0.9);
	legIPfar->SetBorderSize(0);
	legIPfar->SetFillStyle(0);
	TLegend* legIPnear = new TLegend(0.1,0.7,0.48,0.9);
	TLegend *legnonIPfar = new TLegend(0.53, 0.7, 0.9, 0.9);
	TLegend *legnonIPnear = new TLegend(0.1, 0.7, 0.48, 0.9);


// ******************************************
// IP NEAR **********************************
//*******************************************

	c1->cd(2);	
	
	ROOT::Math::XYPoint IPnearTOP(9.689714372596885, 39.98638950777488);
	ROOT::Math::XYPoint IPnearBOT(35.12630991673824, -21.422984435490225);
	
	ROOT::Math::XYPoint IPnearTOP_Target(9.689714372596885+cos(-112.5/180.*pi)*IPnearTOP_Dist,
					     39.98638950777488+sin(-112.5/180.*pi)*IPnearTOP_Dist);

	ROOT::Math::XYPoint IPnearBOT_Target(35.12630991673824  +cos(157.5/180.*pi)*IPnearBOT_Dist,
					     -21.422984435490225+sin(157.5/180.*pi)*IPnearTOP_Dist);
	
	const TVector2 DSensorsTargetsIPnear(IPnearTOP_Target.X()-IPnearBOT_Target.X(),
					     IPnearTOP_Target.Y()-IPnearBOT_Target.Y());
        const double dSensorTargetsIPnear = DSensorsTargetsIPnear.Mod();
	TVector2 pointingDirectionIPnear = DSensorsTargetsIPnear.Rotate(pi/2.);
	TVector2 pointingDirectionIPnear_norm = pointingDirectionIPnear.Unit();
	
	const double scaleIPnear = sqrt(beampipe_r*beampipe_r - dSensorTargetsIPnear*dSensorTargetsIPnear/4);
	ROOT::Math::XYPoint targetCenterIPnear((IPnearTOP_Target.X()+IPnearBOT_Target.X())/2,
					       (IPnearTOP_Target.Y()+IPnearBOT_Target.Y())/2);
	ROOT::Math::XYPoint beampipeCenterIPnear(targetCenterIPnear.X()+scaleIPnear*pointingDirectionIPnear_norm.X(),
						 targetCenterIPnear.Y()+scaleIPnear*pointingDirectionIPnear_norm.Y());
	cout << "Shift of beampipe with respect to CASTOR center: (x|y)" << endl;
	cout << "Near IP: " << beampipeCenterIPnear.X() << "   " << beampipeCenterIPnear.Y() << endl;
	
	TGraph * SensorsIPnear = new TGraph();
	SensorsIPnear->SetMarkerStyle(20);
	SensorsIPnear->SetPoint(0,IPnearTOP.X(),IPnearTOP.Y());
	SensorsIPnear->SetPoint(1,IPnearTOP_Target.X(),IPnearTOP_Target.Y());
	SensorsIPnear->SetPoint(2,IPnearBOT.X(),IPnearBOT.Y());
	SensorsIPnear->SetPoint(3,IPnearBOT_Target.X(),IPnearBOT_Target.Y());
	SensorsIPnear->GetXaxis()->SetLimits(-60.,60.);
	SensorsIPnear->GetHistogram()->SetMaximum(60.);
	SensorsIPnear->GetHistogram()->SetMinimum(-60.);
	SensorsIPnear->Draw("ap");

	TLine* pointing = new TLine();
	pointing->SetLineColor(kBlue);
	pointing->SetLineWidth(2);
	pointing->SetLineStyle(1);
	pointing->DrawLine(IPnearTOP.X(),IPnearTOP.Y(), IPnearTOP_Target.X(),IPnearTOP_Target.Y());
	pointing->DrawLine(IPnearBOT.X(),IPnearBOT.Y(), IPnearBOT_Target.X(),IPnearBOT_Target.Y());
	
	TGraph* CastorCenter = new TGraph;
	CastorCenter->SetPoint(0,0,0);
	CastorCenter->SetMarkerStyle(2);
	CastorCenter->Draw("samep");
	legIPnear->AddEntry(CastorCenter, "CASTOR center", "p");
	
	TGraph* beampipeIPnear = new TGraph();
	beampipeIPnear->SetPoint(0,beampipeCenterIPnear.X(),beampipeCenterIPnear.Y());
	beampipeIPnear->SetMarkerStyle(5);
	beampipeIPnear->Draw("sameP");
	legIPnear->AddEntry(beampipeIPnear, "BP center","p");
	
	
	TEllipse* beamPipeIPnear = new TEllipse(beampipeCenterIPnear.X(),beampipeCenterIPnear.Y(),beampipe_r,beampipe_r);
	beamPipeIPnear->SetFillStyle(0);
	beamPipeIPnear->SetLineColor(1);
	beamPipeIPnear->SetLineStyle(1);
	beamPipeIPnear->SetLineWidth(2);
	beamPipeIPnear->Draw();	
	TEllipse* beamPipeIPnear2 = new TEllipse(beampipeCenterIPnear.X()+maxShift_IPnear_Xout,beampipeCenterIPnear.Y()+maxShift_IPnear_Ydown,beampipe_r+5,beampipe_r+5);
	beamPipeIPnear2->SetFillStyle(0);
	beamPipeIPnear2->SetLineColor(2);
	beamPipeIPnear2->Draw();
	TEllipse* beamPipeIPnear3 = new TEllipse(beampipeCenterIPnear.X()+maxShift_IPnear_Xout,beampipeCenterIPnear.Y()-maxShift_IPnear_Yup,beampipe_r+5,beampipe_r+5);
	beamPipeIPnear3->SetFillStyle(0);
	beamPipeIPnear3->SetLineColor(2);
	beamPipeIPnear3->Draw();

	TGraph* OpeningIPnear = new TGraph();
	OpeningIPnear->SetPoint(0,beampipeCenterIPnear.X()+maxOpening ,-60);
	OpeningIPnear->SetPoint(1,beampipeCenterIPnear.X()+maxOpening ,60);
	OpeningIPnear->SetLineColor(kGreen+1);
	OpeningIPnear->Draw("samel");

	TGraph* shapeIPnear = new TGraph();
	shapeIPnear->SetLineWidth(2);
	shapeIPnear->SetLineStyle(1);
	shapeIPnear->SetPoint(0,0,castor_inner_octant_radius);
	shapeIPnear->SetPoint(1,sin(45./180.*pi)*castor_inner_octant_radius,cos(45./180.*pi)*castor_inner_octant_radius);
	shapeIPnear->SetPoint(2,castor_inner_octant_radius,0);
	shapeIPnear->SetPoint(3,sin(135./180.*pi)*castor_inner_octant_radius,cos(135./180.*pi)*castor_inner_octant_radius);
	shapeIPnear->SetPoint(4,0,-castor_inner_octant_radius);
	shapeIPnear->Draw("samel");
	
	legIPnear->SetHeader("IP side NEAR");
	legIPnear->AddEntry(shapeIPnear, "CASTOR", "l");
	legIPnear->AddEntry(beamPipeIPnear, "beampipe position", "l");
	legIPnear->AddEntry(beamPipeIPnear2, "beampipe protection area", "l");
	legIPnear->AddEntry(OpeningIPnear, "max allowed opening", "l");
	legIPnear->Draw();

// ******************************************
// IP FAR  **********************************
//*******************************************
	c1->cd(1);
	
	ROOT::Math::XYPoint IPfarTOP(-9.689714372596882, 39.98638950777488);

	ROOT::Math::XYPoint IPfarBOT(-39.98638950777488, -9.689714372596889);
	ROOT::Math::XYPoint IPfarTOP_Target(IPfarTOP.X()+cos(-67.5/180.*pi)*IPfarTOP_Dist,
                                            IPfarTOP.Y()+sin(-67.5/180.*pi)*IPfarTOP_Dist);

	ROOT::Math::XYPoint IPfarBOT_Target(IPfarBOT.X()+cos(22.5/180.*pi)*IPfarBOT_Dist,
                                            IPfarBOT.Y()+sin(22.5/180.*pi)*IPfarTOP_Dist);

	TVector2 DSensorsTargetsIPfar(IPfarBOT_Target.X()-IPfarTOP_Target.X(),IPfarBOT_Target.Y()-IPfarTOP_Target.Y());
	double dSensorTargetsIPfar = DSensorsTargetsIPfar.Mod();
	TVector2 pointingDirectionIPfar = DSensorsTargetsIPfar.Rotate(pi/2.);
	TVector2 pointingDirectionIPfar_norm = pointingDirectionIPfar.Unit();

	double scaleIPfar = sqrt(beampipe_r*beampipe_r-dSensorTargetsIPfar*dSensorTargetsIPfar/4);
	ROOT::Math::XYPoint targetCenterIPfar((IPfarTOP_Target.X()+IPfarBOT_Target.X())/2, (IPfarTOP_Target.Y()+IPfarBOT_Target.Y())/2);
	ROOT::Math::XYPoint beampipeCenterIPfar(targetCenterIPfar.X()+scaleIPfar*pointingDirectionIPfar_norm.X(),targetCenterIPfar.Y()+scaleIPfar*pointingDirectionIPfar_norm.Y());
	cout << "far IP: " << beampipeCenterIPfar.X() << "   " << beampipeCenterIPfar.Y() << endl;
		
	TGraph * SensorsIPfar = new TGraph();
	SensorsIPfar->SetMarkerStyle(20);

	SensorsIPfar->SetPoint(0,IPfarTOP.X(),IPfarTOP.Y());
	SensorsIPfar->SetPoint(1,IPfarTOP_Target.X(),IPfarTOP_Target.Y());
	SensorsIPfar->SetPoint(2,IPfarBOT.X(),IPfarBOT.Y());
	SensorsIPfar->SetPoint(3,IPfarBOT_Target.X(),IPfarBOT_Target.Y());
	SensorsIPfar->GetXaxis()->SetLimits(-60.,60.);
	SensorsIPfar->GetHistogram()->SetMaximum(60.);
	SensorsIPfar->GetHistogram()->SetMinimum(-60.);
	SensorsIPfar->Draw("ap");


	pointing->DrawLine(IPfarTOP.X(),IPfarTOP.Y(), IPfarTOP_Target.X(),IPfarTOP_Target.Y());
	pointing->DrawLine(IPfarBOT.X(),IPfarBOT.Y(), IPfarBOT_Target.X(),IPfarBOT_Target.Y());


	CastorCenter->Draw("samep");

	TGraph* beampipeIPfar = new TGraph();
	beampipeIPfar->SetPoint(0,beampipeCenterIPfar.X(),beampipeCenterIPfar.Y());
	beampipeIPfar->SetMarkerStyle(5);
	beampipeIPfar->Draw("sameP");
	
	TEllipse* beamPipeIPfar = new TEllipse(beampipeCenterIPfar.X(),beampipeCenterIPfar.Y(),beampipe_r,beampipe_r);
	beamPipeIPfar->SetFillStyle(0);
	beamPipeIPfar->SetLineColor(1);
	//beamPipeIPfar->SetLineStyle(2);
	beamPipeIPfar->SetLineStyle(1);
	beamPipeIPfar->SetLineWidth(2);
	beamPipeIPfar->Draw();
	TEllipse* beamPipeIPfar2 = new TEllipse(beampipeCenterIPfar.X()-maxShift_IPfar_Xout,beampipeCenterIPfar.Y()+maxShift_IPfar_Ydown,beampipe_r+5,beampipe_r+5);
	beamPipeIPfar2->SetFillStyle(0);
	beamPipeIPfar2->SetLineColor(2);
	beamPipeIPfar2->Draw();
	TEllipse* beamPipeIPfar3 = new TEllipse(beampipeCenterIPfar.X()-maxShift_IPfar_Xout,beampipeCenterIPfar.Y()-maxShift_IPfar_Yup,beampipe_r+5,beampipe_r+5);
	beamPipeIPfar3->SetFillStyle(0);
	beamPipeIPfar3->SetLineColor(2);
	beamPipeIPfar3->Draw();

	TGraph* OpeningIPfar = new TGraph();
	OpeningIPfar->SetPoint(0,beampipeCenterIPfar.X()-maxOpening ,-60);
	OpeningIPfar->SetPoint(1,beampipeCenterIPfar.X()-maxOpening ,60);
	OpeningIPfar->SetLineColor(kGreen+1);
	OpeningIPfar->Draw("samel");

	TGraph* shapeIPfar = new TGraph();
	shapeIPfar->SetLineWidth(2);
	shapeIPfar->SetLineStyle(1);
	shapeIPfar->SetPoint(0,0,castor_inner_octant_radius);
	shapeIPfar->SetPoint(1,sin(-45./180.*pi)*castor_inner_octant_radius,cos(-45./180.*pi)*castor_inner_octant_radius);
	shapeIPfar->SetPoint(2,-castor_inner_octant_radius,0);
	shapeIPfar->SetPoint(3,sin(-135./180.*pi)*castor_inner_octant_radius,cos(-135./180.*pi)*castor_inner_octant_radius);
	shapeIPfar->SetPoint(4,0,-castor_inner_octant_radius);
	shapeIPfar->Draw("samel");

	legIPfar->SetHeader("IP side FAR");
	legIPfar->AddEntry(shapeIPfar ,"CASTOR","l");
	legIPfar->AddEntry(beamPipeIPfar ,"BP position","l");
	legIPfar->AddEntry(beamPipeIPfar2,"BP protection area","l");
	legIPfar->AddEntry(OpeningIPfar,"max allowed opening","l");
  legIPfar->Draw();

  // ******************************************
  // non-IP NEAR ******************************
  // ******************************************

  c1->cd(4);

  ROOT::Math::XYPoint nonIPnearTOP(13.488707010283298, 38.41279523388963);

  ROOT::Math::XYPoint nonIPnearMID(44, -1.6);

  ROOT::Math::XYPoint nonIPnearBOT(14.447693965030012, -38.01556983109467);
  ROOT::Math::XYPoint nonIPnearTOP_Target(
      nonIPnearTOP.X() + cos(-112.5 / 180. * pi) * nonIPnearTOP_Dist,
      nonIPnearTOP.Y() + sin(-112.5 / 180. * pi) * nonIPnearTOP_Dist);

  ROOT::Math::XYPoint nonIPnearMID_Target(
      nonIPnearMID.X() + cos(180 / 180. * pi) * nonIPnearMID_Dist,
      nonIPnearMID.Y() + sin(180 / 180. * pi) * nonIPnearMID_Dist);

  ROOT::Math::XYPoint nonIPnearBOT_Target(
      nonIPnearBOT.X() + cos(112.5 / 180. * pi) * nonIPnearBOT_Dist,
      nonIPnearBOT.Y() + sin(112.5 / 180. * pi) * nonIPnearBOT_Dist);

  TVector2 DSensorsTargetsnonIPnear1(
      nonIPnearTOP_Target.X() - nonIPnearBOT_Target.X(),
      nonIPnearTOP_Target.Y() - nonIPnearBOT_Target.Y());
  const double dSensorTargetsnonIPnear1 = DSensorsTargetsnonIPnear1.Mod();
  TVector2 pointingDirectionnonIPnear1 =
      DSensorsTargetsnonIPnear1.Rotate(pi / 2.);
  TVector2 pointingDirectionnonIPnear_norm1 =
      pointingDirectionnonIPnear1.Unit();
  double scalenonIPnear1 =
      sqrt(beampipe_r * beampipe_r -
           dSensorTargetsnonIPnear1 * dSensorTargetsnonIPnear1 / 4);
  ROOT::Math::XYPoint targetCenternonIPnear1(
      (nonIPnearTOP_Target.X() + nonIPnearBOT_Target.X()) / 2,
      (nonIPnearTOP_Target.Y() + nonIPnearBOT_Target.Y()) / 2);

  TVector2 DSensorsTargetsnonIPnear2(
      nonIPnearTOP_Target.X() - nonIPnearMID_Target.X(),
      nonIPnearTOP_Target.Y() - nonIPnearMID_Target.Y());
  double dSensorTargetsnonIPnear2 = DSensorsTargetsnonIPnear2.Mod();
  TVector2 pointingDirectionnonIPnear2 =
      DSensorsTargetsnonIPnear2.Rotate(pi / 2.);
  TVector2 pointingDirectionnonIPnear_norm2 =
      pointingDirectionnonIPnear2.Unit();
  double scalenonIPnear2 =
      sqrt(beampipe_r * beampipe_r -
           dSensorTargetsnonIPnear2 * dSensorTargetsnonIPnear2 / 4);
  ROOT::Math::XYPoint targetCenternonIPnear2(
      (nonIPnearTOP_Target.X() + nonIPnearMID_Target.X()) / 2,
      (nonIPnearTOP_Target.Y() + nonIPnearMID_Target.Y()) / 2);

  TVector2 DSensorsTargetsnonIPnear3(
      nonIPnearMID_Target.X() - nonIPnearBOT_Target.X(),
      nonIPnearMID_Target.Y() - nonIPnearBOT_Target.Y());
  double dSensorTargetsnonIPnear3 = DSensorsTargetsnonIPnear3.Mod();
  TVector2 pointingDirectionnonIPnear3 =
      DSensorsTargetsnonIPnear3.Rotate(pi / 2.);
  TVector2 pointingDirectionnonIPnear_norm3 =
      pointingDirectionnonIPnear3.Unit();
  double scalenonIPnear3 =
      sqrt(beampipe_r * beampipe_r -
           dSensorTargetsnonIPnear3 * dSensorTargetsnonIPnear3 / 4);
  ROOT::Math::XYPoint targetCenternonIPnear3(
      (nonIPnearMID_Target.X() + nonIPnearBOT_Target.X()) / 2,
      (nonIPnearMID_Target.Y() + nonIPnearBOT_Target.Y()) / 2);

  ROOT::Math::XYPoint beampipeCenternonIPnear1(
      targetCenternonIPnear1.X() +
          scalenonIPnear1 * pointingDirectionnonIPnear_norm1.X(),
      targetCenternonIPnear1.Y() +
          scalenonIPnear1 * pointingDirectionnonIPnear_norm1.Y());
  ROOT::Math::XYPoint beampipeCenternonIPnear2(
      targetCenternonIPnear2.X() +
          scalenonIPnear2 * pointingDirectionnonIPnear_norm2.X(),
      targetCenternonIPnear2.Y() +
          scalenonIPnear2 * pointingDirectionnonIPnear_norm2.Y());
  ROOT::Math::XYPoint beampipeCenternonIPnear3(
      targetCenternonIPnear3.X() +
          scalenonIPnear3 * pointingDirectionnonIPnear_norm3.X(),
      targetCenternonIPnear3.Y() +
          scalenonIPnear3 * pointingDirectionnonIPnear_norm3.Y());

  ROOT::Math::XYPoint beampipeCenternonIPnearCOG(
      (beampipeCenternonIPnear1.X() + beampipeCenternonIPnear2.X() +
       beampipeCenternonIPnear3.X()) /
          3.,
      (beampipeCenternonIPnear1.Y() + beampipeCenternonIPnear2.Y() +
       beampipeCenternonIPnear3.Y()) /
          3.);
  cout << "Near nonIP: " << beampipeCenternonIPnearCOG.X() << "   "
       << beampipeCenternonIPnearCOG.Y() << endl;

  TGraph *SensorsnonIPnear = new TGraph();
  SensorsnonIPnear->SetMarkerStyle(20);

  SensorsnonIPnear->SetPoint(0, nonIPnearTOP.X(), nonIPnearTOP.Y());
  SensorsnonIPnear->SetPoint(1, nonIPnearTOP_Target.X(),
                             nonIPnearTOP_Target.Y());
  SensorsnonIPnear->SetPoint(2, nonIPnearMID.X(), nonIPnearMID.Y());
  SensorsnonIPnear->SetPoint(3, nonIPnearMID_Target.X(),
                             nonIPnearMID_Target.Y());
  SensorsnonIPnear->SetPoint(4, nonIPnearBOT.X(), nonIPnearBOT.Y());
  SensorsnonIPnear->SetPoint(5, nonIPnearBOT_Target.X(),
                             nonIPnearBOT_Target.Y());
  SensorsnonIPnear->GetXaxis()->SetLimits(-60., 60.);
  SensorsnonIPnear->GetHistogram()->SetMaximum(60.);
  SensorsnonIPnear->GetHistogram()->SetMinimum(-60.);
  SensorsnonIPnear->Draw("ap");
  
  pointing->DrawLine(nonIPnearTOP.X(),nonIPnearTOP.Y(), nonIPnearTOP_Target.X(),nonIPnearTOP_Target.Y());
  pointing->DrawLine(nonIPnearMID.X(),nonIPnearMID.Y(), nonIPnearMID_Target.X(),nonIPnearMID_Target.Y());
  pointing->DrawLine(nonIPnearBOT.X(),nonIPnearBOT.Y(), nonIPnearBOT_Target.X(),nonIPnearBOT_Target.Y());
  
  CastorCenter->Draw("samep");

  TGraph *beampipenonIPnear = new TGraph();
  beampipenonIPnear->SetPoint(0, beampipeCenternonIPnearCOG.X(),
                              beampipeCenternonIPnearCOG.Y());
  beampipenonIPnear->SetMarkerStyle(5);
  beampipenonIPnear->Draw("sameP");
  TEllipse *circlenonIPnear =
      new TEllipse(beampipeCenternonIPnearCOG.X(),
                   beampipeCenternonIPnearCOG.Y(), beampipe_r, beampipe_r);
  circlenonIPnear->SetFillStyle(0);
  circlenonIPnear->SetLineColor(1);
  circlenonIPnear->SetLineStyle(2);
  circlenonIPnear->Draw();
  TEllipse *circlenonIPnear2 =
      new TEllipse(beampipeCenternonIPnearCOG.X() + maxShift_nonIPnear_Xout,
                   beampipeCenternonIPnearCOG.Y() + maxShift_nonIPnear_Ydown,
                   beampipe_r + 5, beampipe_r + 5);
  circlenonIPnear2->SetFillStyle(0);
  circlenonIPnear2->SetLineColor(2);
  circlenonIPnear2->Draw();
  TEllipse *circlenonIPnear3 =
      new TEllipse(beampipeCenternonIPnearCOG.X() + maxShift_nonIPnear_Xout,
                   beampipeCenternonIPnearCOG.Y() - maxShift_nonIPnear_Yup,
                   beampipe_r + 5, beampipe_r + 5);
  circlenonIPnear3->SetFillStyle(0);
  circlenonIPnear3->SetLineColor(2);
  circlenonIPnear3->Draw();

  TGraph *OpeningnonIPnear = new TGraph();
  OpeningnonIPnear->Draw("samel");
  OpeningnonIPnear->SetPoint(0, beampipeCenternonIPnearCOG.X() + maxOpening,
                             -60);
  OpeningnonIPnear->SetPoint(1, beampipeCenternonIPnearCOG.X() + maxOpening,
                             60);
  OpeningnonIPnear->SetLineColor(kGreen+1);
  OpeningnonIPnear->Draw("samel");

  TGraph *shapenonIPnear = new TGraph();
  shapenonIPnear->SetLineWidth(2);
  shapenonIPnear->SetLineStyle(1);
  shapenonIPnear->SetPoint(0, 0, castor_inner_octant_radius);
  shapenonIPnear->SetPoint(1, sin(45. / 180. * pi) * castor_inner_octant_radius,
                           cos(45. / 180. * pi) * castor_inner_octant_radius);
  shapenonIPnear->SetPoint(2, castor_inner_octant_radius, 0);
  shapenonIPnear->SetPoint(3,
                           sin(135. / 180. * pi) * castor_inner_octant_radius,
                           cos(135. / 180. * pi) * castor_inner_octant_radius);
  shapenonIPnear->SetPoint(4, 0, -castor_inner_octant_radius);
  shapenonIPnear->Draw("samel");

  legnonIPnear->SetHeader("non-IP side NEAR");
  legnonIPnear->AddEntry(shapenonIPnear, "CASTOR", "l");
  legnonIPnear->AddEntry(circlenonIPnear, "BP position", "l");
  legnonIPnear->AddEntry(circlenonIPnear2, "BP protection area", "l");
  legnonIPnear->AddEntry(OpeningnonIPnear, "max allowed opening", "l");
  legnonIPnear->Draw();

  // ******************************************
  // non-IP far *******************************
  // ******************************************

  c1->cd(3);

  ROOT::Math::XYPoint nonIPfarTOP(-16.700112265292525, 37.082587622988584);

  ROOT::Math::XYPoint nonIPfarMID(-44, 1.6);

  ROOT::Math::XYPoint nonIPfarBOT(-13.488707010283294, -38.41279523388963);
  ROOT::Math::XYPoint nonIPfarTOP_Target(
      nonIPfarTOP.X() + cos(-67.5 / 180. * pi) * nonIPfarTOP_Dist,
      nonIPfarTOP.Y() + sin(-67.5 / 180. * pi) * nonIPfarTOP_Dist);
  
  ROOT::Math::XYPoint nonIPfarMID_Target(
      nonIPfarMID.X() + cos(0. / 180. * pi) * nonIPfarMID_Dist,
      nonIPfarMID.Y() + sin(0. / 180. * pi) * nonIPfarMID_Dist);
  
  ROOT::Math::XYPoint nonIPfarBOT_Target(
      nonIPfarBOT.X() + cos(67.5 / 180. * pi) * nonIPfarBOT_Dist,
      nonIPfarBOT.Y() + sin(67.5 / 180. * pi) * nonIPfarBOT_Dist);

  TVector2 DSensorsTargetsnonIPfar1(
      nonIPfarBOT_Target.X() - nonIPfarTOP_Target.X(),
      nonIPfarBOT_Target.Y() - nonIPfarTOP_Target.Y());
  double dSensorTargetsnonIPfar1 = DSensorsTargetsnonIPfar1.Mod();
  TVector2 pointingDirectionnonIPfar1 =
      DSensorsTargetsnonIPfar1.Rotate(pi / 2.);
  TVector2 pointingDirectionnonIPfar_norm1 = pointingDirectionnonIPfar1.Unit();
  TVector2 DSensorsTargetsnonIPfar2(
      nonIPfarBOT_Target.X() - nonIPfarMID_Target.X(),
      nonIPfarBOT_Target.Y() - nonIPfarMID_Target.Y());
  double dSensorTargetsnonIPfar2 = DSensorsTargetsnonIPfar2.Mod();
  TVector2 pointingDirectionnonIPfar2 =
      DSensorsTargetsnonIPfar2.Rotate(pi / 2.);
  TVector2 pointingDirectionnonIPfar_norm2 = pointingDirectionnonIPfar2.Unit();
  TVector2 DSensorsTargetsnonIPfar3(
      nonIPfarMID_Target.X() - nonIPfarTOP_Target.X(),
      nonIPfarMID_Target.Y() - nonIPfarTOP_Target.Y());
  double dSensorTargetsnonIPfar3 = DSensorsTargetsnonIPfar3.Mod();
  TVector2 pointingDirectionnonIPfar3 =
      DSensorsTargetsnonIPfar3.Rotate(pi / 2.);
  TVector2 pointingDirectionnonIPfar_norm3 = pointingDirectionnonIPfar3.Unit();

  double scalenonIPfar1 =
      sqrt(beampipe_r * beampipe_r -
           dSensorTargetsnonIPfar1 * dSensorTargetsnonIPfar1 / 4);
  double scalenonIPfar2 =
      sqrt(beampipe_r * beampipe_r -
           dSensorTargetsnonIPfar2 * dSensorTargetsnonIPfar2 / 4);
  double scalenonIPfar3 =
      sqrt(beampipe_r * beampipe_r -
           dSensorTargetsnonIPfar3 * dSensorTargetsnonIPfar3 / 4);

  ROOT::Math::XYPoint targetCenternonIPfar1(
      (nonIPfarTOP_Target.X() + nonIPfarBOT_Target.X()) / 2,
      (nonIPfarTOP_Target.Y() + nonIPfarBOT_Target.Y()) / 2);
  ROOT::Math::XYPoint targetCenternonIPfar2(
      (nonIPfarTOP_Target.X() + nonIPfarMID_Target.X()) / 2,
      (nonIPfarTOP_Target.Y() + nonIPfarMID_Target.Y()) / 2);
  ROOT::Math::XYPoint targetCenternonIPfar3(
      (nonIPfarMID_Target.X() + nonIPfarBOT_Target.X()) / 2,
      (nonIPfarMID_Target.Y() + nonIPfarBOT_Target.Y()) / 2);

  ROOT::Math::XYPoint beampipeCenternonIPfar1(
      targetCenternonIPfar1.X() +
          scalenonIPfar1 * pointingDirectionnonIPfar_norm1.X(),
      targetCenternonIPfar1.Y() +
          scalenonIPfar1 * pointingDirectionnonIPfar_norm1.Y());
  ROOT::Math::XYPoint beampipeCenternonIPfar2(
      targetCenternonIPfar2.X() +
          scalenonIPfar2 * pointingDirectionnonIPfar_norm2.X(),
      targetCenternonIPfar2.Y() +
          scalenonIPfar2 * pointingDirectionnonIPfar_norm2.Y());
  ROOT::Math::XYPoint beampipeCenternonIPfar3(
      targetCenternonIPfar3.X() +
          scalenonIPfar3 * pointingDirectionnonIPfar_norm3.X(),
      targetCenternonIPfar3.Y() +
          scalenonIPfar3 * pointingDirectionnonIPfar_norm3.Y());

  ROOT::Math::XYPoint beampipeCenternonIPfarCOG(
      (beampipeCenternonIPfar1.X() + beampipeCenternonIPfar2.X() +
       beampipeCenternonIPfar3.X()) /
          3.,
      (beampipeCenternonIPfar1.Y() + beampipeCenternonIPfar2.Y() +
       beampipeCenternonIPfar3.Y()) /
          3.);
  cout << "far nonIP: " << beampipeCenternonIPfarCOG.X() << "   "
       << beampipeCenternonIPfarCOG.Y() << endl;

  TGraph *SensorsnonIPfar = new TGraph();
  SensorsnonIPfar->SetMarkerStyle(20);

  SensorsnonIPfar->SetPoint(0, nonIPfarTOP.X(), nonIPfarTOP.Y());
  SensorsnonIPfar->SetPoint(1, nonIPfarTOP_Target.X(), nonIPfarTOP_Target.Y());
  SensorsnonIPfar->SetPoint(2, nonIPfarMID.X(), nonIPfarMID.Y());
  SensorsnonIPfar->SetPoint(3, nonIPfarMID_Target.X(), nonIPfarMID_Target.Y());
  SensorsnonIPfar->SetPoint(4, nonIPfarBOT.X(), nonIPfarBOT.Y());
  SensorsnonIPfar->SetPoint(5, nonIPfarBOT_Target.X(), nonIPfarBOT_Target.Y());
  SensorsnonIPfar->GetXaxis()->SetLimits(-60., 60.);
  SensorsnonIPfar->GetHistogram()->SetMaximum(60.);
  SensorsnonIPfar->GetHistogram()->SetMinimum(-60.);
  SensorsnonIPfar->Draw("ap");

  pointing->DrawLine(nonIPfarTOP.X(),nonIPfarTOP.Y(), nonIPfarTOP_Target.X(),nonIPfarTOP_Target.Y());
  pointing->DrawLine(nonIPfarMID.X(),nonIPfarMID.Y(), nonIPfarMID_Target.X(),nonIPfarMID_Target.Y());
  pointing->DrawLine(nonIPfarBOT.X(),nonIPfarBOT.Y(), nonIPfarBOT_Target.X(),nonIPfarBOT_Target.Y());

  CastorCenter->Draw("samep");

  TGraph *beampipenonIPfar = new TGraph();
  beampipenonIPfar->SetPoint(0, beampipeCenternonIPfarCOG.X(),
                             beampipeCenternonIPfarCOG.Y());
  beampipenonIPfar->SetMarkerStyle(5);
  beampipenonIPfar->Draw("sameP");
  TEllipse *circlenonIPfar =
      new TEllipse(beampipeCenternonIPfarCOG.X(), beampipeCenternonIPfarCOG.Y(),
                   beampipe_r, beampipe_r);
  circlenonIPfar->SetFillStyle(0);
  circlenonIPfar->SetLineColor(1);
  circlenonIPfar->SetLineStyle(2);
  circlenonIPfar->Draw();
  TEllipse *circlenonIPfar2 =
      new TEllipse(beampipeCenternonIPfarCOG.X() - maxShift_nonIPfar_Xout,
                   beampipeCenternonIPfarCOG.Y() + maxShift_nonIPfar_Ydown,
                   beampipe_r + 5, beampipe_r + 5);
  circlenonIPfar2->SetFillStyle(0);
  circlenonIPfar2->SetLineColor(2);
  circlenonIPfar2->Draw();
  TEllipse *circlenonIPfar3 =
      new TEllipse(beampipeCenternonIPfarCOG.X() - maxShift_nonIPfar_Xout,
                   beampipeCenternonIPfarCOG.Y() - maxShift_nonIPfar_Yup,
                   beampipe_r + 5, beampipe_r + 5);
  circlenonIPfar3->SetFillStyle(0);
  circlenonIPfar3->SetLineColor(2);
  circlenonIPfar3->Draw();

  TGraph *OpeningnonIPfar = new TGraph();
  OpeningnonIPfar->Draw("samel");
  OpeningnonIPfar->SetPoint(0, beampipeCenternonIPfarCOG.X() - maxOpening, -60);
  OpeningnonIPfar->SetPoint(1, beampipeCenternonIPfarCOG.X() - maxOpening, 60);
  OpeningnonIPfar->SetLineColor(kGreen+1);
  OpeningnonIPfar->Draw("samel");
  
  TGraph *shapenonIPfar = new TGraph();
  shapenonIPfar->SetLineWidth(2);
  shapenonIPfar->SetLineStyle(1);
  shapenonIPfar->SetPoint(0, 0, castor_inner_octant_radius);
  shapenonIPfar->SetPoint(1, sin(-45. / 180. * pi) * castor_inner_octant_radius,
                          cos(45. / 180. * pi) * castor_inner_octant_radius);
  shapenonIPfar->SetPoint(2, -castor_inner_octant_radius, 0);
  shapenonIPfar->SetPoint(3,
                          sin(-135. / 180. * pi) * castor_inner_octant_radius,
                          cos(135. / 180. * pi) * castor_inner_octant_radius);
  shapenonIPfar->SetPoint(4, 0, -castor_inner_octant_radius);
  shapenonIPfar->Draw("samel");
  
  legnonIPfar->SetHeader("non-IP side FAR");
  legnonIPfar->AddEntry(shapenonIPfar, "CASTOR", "l");
  legnonIPfar->AddEntry(circlenonIPfar, "BP position", "l");
  legnonIPfar->AddEntry(circlenonIPfar2, "BP protection area", "l");
  legnonIPfar->AddEntry(OpeningnonIPfar, "max allowed opening", "l");
  legnonIPfar->Draw();
}
