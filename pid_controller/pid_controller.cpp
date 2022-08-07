/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  kp = Kpi;
  ki = Kii;
  kd = Kdi;

  lim_maxi = output_lim_maxi;
  lim_mini = output_lim_mini;

  p_error = 0;
  d_error = 0;
  i_error = 0;

  delta_time = 0;

}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
  //proportional
  p_error = cte;

  //integral
  i_error += cte * delta_time;
  // if delta_time <= 0 d error to 0
  if (delta_time <= 0){
     d_error = 0;
     return;
  }
  // differentiable
  d_error = (cte - p_error)/delta_time;
 
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double control;

    // calculate the total error
    control = -kp * p_error - ki * i_error - kd * d_error;

    // this return a value in the specified interval
    control = max(min(control, lim_maxi), lim_mini);
    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
  delta_time = new_delta_time;
}