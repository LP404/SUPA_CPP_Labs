///I was talking to another student and they suggested that I combine all the custom functions into one class and add a flag to tell it what to run
///Why didn't I think of that?

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include "FiniteFunctions2.h"
#include <filesystem> //To check extensions in a nice way

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
};

//initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
};
//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
};


Ex34Functions::Ex34Functions(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
};

Ex34Functions::Ex34Functions(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

Ex34Functions::~Ex34Functions(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
};


/*
###################
//Data In
###################
*/ 



std::vector<double> Ex34Functions::ReadFunc(std::string fName){

///Opens a file, ready for reading in data
std::ifstream myInput(fName);

///Checks if this file is open, terminates function if that is not the case. Notifies user
if(!myInput.is_open()){
    std::cout<<"File is not open"<<std::endl;
    exit(1);
}

///Initilises variables that will be used to store data
double valHold;
std::vector<double> val;
std::string strHold;
std::string line;

///Reads in each data from each line, seperated by the comma
///The first loop will read in data but not assign the strings to anything
///Appends data to two vectors, while converting the string it reads in, to a float
while(getline(myInput,line)){
    //The loop will 'discard' the string values
    std::stringstream findLine(line);
    getline(findLine,strHold);
    val.push_back(std::stod(strHold));
}

///Closes the file and returns values out of the fucntion
myInput.close();
return val;
}


/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};


void Ex34Functions::SetGaussParams(double Rmu,double Rstd){
m_Mu = Rmu;
m_StdDev = Rstd;
};
void Ex34Functions::SetCauchLorParams(double Rx0,double Rgamma){
m_x0 = Rx0;
m_Gamma = Rgamma;
};

void Ex34Functions::SetCrystalParams(double Ralpha,double Rn, double RstDev){
m_Alpha = Ralpha;
m_n = Rn;
m_stanDev = RstDev;
};


void Ex34Functions::SetCrystalAverage(double Ravg){m_Average = Ravg;};

void Ex34Functions::SetCoefs(double Ralpha, double Rn, double RstDev){

m_A = (pow((Rn/Ralpha),Rn))*exp(-((Ralpha*Ralpha)/2));
m_B = (Rn/Rn)-Ralpha;
m_C = (Rn/Ralpha)*(1/(Rn-1))*exp(-((Ralpha*Ralpha)/2));
m_D = sqrt(M_PI_2)*(1+std::erf(Rn/sqrt(2)));
m_N = 1/(RstDev*(m_C+m_D));
};

/*
###################
//Getters
###################
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

double Ex34Functions::gdistMu() {return m_Mu;};
double Ex34Functions::gdistStandardDev() {return m_StdDev;};

double Ex34Functions::CoLoX0() {return m_x0;};
double Ex34Functions::CoLoGamma() {return m_Gamma;};


double Ex34Functions::crystAlpha() {return m_Alpha;}; 
double Ex34Functions::crystn() {return m_n;}; 
double Ex34Functions::crystStanDev() {return m_stanDev;};
double Ex34Functions::crystalAverage(){return m_Average;};

std::tuple<double, double, double, double, double> Ex34Functions::crystCoeff() {
  return std::tuple<double, double, double, double, double>{m_A, m_B, m_C, m_D, m_N};};


/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);}; //(overridable)

double Ex34Functions::Gaussian(double x) {
return (1.0/(gdistStandardDev()*(sqrt(2*M_PI))))*exp((-1.0/2.0)*(((x-gdistMu())/gdistStandardDev())*((x-gdistMu())/gdistStandardDev())));  
};

double Ex34Functions::CauchyLorentz(double x) {
   return (1.0/(M_PI*CoLoGamma()*(1.0+(((x-CoLoX0())/CoLoGamma())*((x-CoLoX0())/CoLoGamma())))));
};

//This is probably very inefficent
double Ex34Functions::CrystalBall(double x) {
      double a;
      double b;
      double A;
      double B;
      double C;
      double D;
      double N;

      auto crstCoeffs = crystCoeff();
        A = std::get<0>(crstCoeffs);
        B = std::get<1>(crstCoeffs);
        C = std::get<2>(crstCoeffs);
        D = std::get<2>(crstCoeffs);
        N = std::get<2>(crstCoeffs);

      ///The average of an evenly space distrubtion should be equal to the sum of the start and end / 2

    if (((x-crystalAverage())/crystStanDev()) <= -crystAlpha()){
        return (A*pow((B-((x-crystalAverage())/crystStanDev())),-crystn()));
    } else {
        return (exp(-((x-crystalAverage())*(x-crystalAverage()))/(2*crystStanDev()*crystStanDev())));
    }
};

double Ex34Functions::callFunction(double x) {
    if (selectDist == 0) {
        return this->Gaussian(x);}
    else if (selectDist == 1) {
        return this->CauchyLorentz(x);}
    else if (selectDist == 2) {
        return this->CrystalBall(x);}
    else {
        std::cout << "Invaid input, terminating" << std::endl;
        exit(1);
    }
};

/*
###################
Integration by hand (output needed to normalise function when plotting)
###################
*/ 
double FiniteFunction::integrate(int Ndiv){ //private
  //Integration Steps
  double Sol = 0;
  double step = (m_RMax - m_RMin)/(double)Ndiv;
  for (double i=m_RMin; i<m_RMax; i+=step) {
    Sol += (callFunction(i)*step);
  }
  return Sol;  
}
double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}

/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}


/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins-1){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}