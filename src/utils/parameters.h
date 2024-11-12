#ifndef parameters_h
#define parameters_h

#include <cmath>

const float pi = 3.1416;
const float g = 9.81;     

const float a2 = 1.203e-07; 
const float a1 = 5.516e-12; 

const float kl = 1.607e-08;
const float kd = 1.309e-10; 


const float m = 30.0e-3;   
const float I_xx = 16.0e-6; 
const float I_yy = 16.0e-6; 
const float I_zz = 29.0e-6; 
const float l = 33.0e-3;  

const float dt = 0.002; 
const float wc = 1; 
const float alpha = (wc*dt)/(1+wc*dt); 

const float Ts_phi = 0.3;   
const float UP_phi = 0.005; 
const float zeta_phi = abs(log(UP_phi))/sqrt((log(UP_phi)*log(UP_phi)) + pi*pi);
const float wn_phi = 4/(zeta_phi*Ts_phi);   
const float kp_phi = wn_phi*wn_phi;
const float kd_phi = 2*zeta_phi*wn_phi; 

const float kp_theta = kp_phi; 
const float kd_theta = kd_phi;  

const float Ts_psi= 0.6;  
const float UP_psi = 0.005;
const float zeta_psi = abs(log(UP_phi))/sqrt((log(UP_phi)*log(UP_phi)) + pi*pi); 
const float wn_psi = 4/(zeta_phi*Ts_phi); 
const float kp_psi = wn_phi*wn_phi;
const float kd_psi = 2*zeta_phi*wn_phi;  

const float dt_range = 0.05;
const float wc_ve = 10.0;
const float l_ve = wc_ve;
const float zeta_ve = sqrt(2.0)/2.0;
const float l_1 = wc_ve*wc_ve;
const float l_2 = 2.0*zeta_ve*wc_ve;

const float Ts_vc= 2.0;   
const float UP_vc = 0.005; 
const float zeta_vc = abs(log(UP_vc))/sqrt((log(UP_vc)*log(UP_vc)) + pi*pi);  
const float wn_vc = 4/(zeta_vc*Ts_vc);  
const float kp_vc = wn_vc*wn_vc;
const float kd_vc = 2*zeta_vc*wn_vc;  

const float gamma = 42.0*pi/180.0;
const float W = 420.0;
const float sigma = 2.0*tan(gamma/2.0)/(W*dt);
const float l_eh = 50.0;

const float Ts_hc= 2.0; 
const float UP_hc = 0.005;
const float zeta_hc = abs(log(UP_hc))/sqrt((log(UP_hc)*log(UP_hc)) + pi*pi); 
const float wn_hc = 4/(zeta_hc*Ts_hc);
const float kp_hc = wn_hc*wn_hc;
const float kd_hc = 2*zeta_hc*wn_hc;

#endif