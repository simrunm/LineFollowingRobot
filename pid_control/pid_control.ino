void setup() {
  // put your setup code here, to run once:

}

void loop() {
  typedef struct
{
real_t derState; // Last position input
real_t integratState; // Integrator state
real_t integratMax, // Maximum and minimum
integratMin; // allowable integrator state
real_t integratGain, // integral gain
propGain, // proportional gain
derGain; // derivative gain
} SPid;
real_t UpdatePID(SPid * pid, real_t error, real_t position)
{
real_t pTerm, dTerm, iTerm;
pTerm = pid->propGain * error; // calculate the proportional term
// calculate the integral state with appropriate limiting
pid->integratState += error;
// Limit the integrator state if necessary
if (pid->integratState > pid->integratMax)
{
pid->integratState = pid->integratMax;
}
else if (pid->integratState < pid->integratMin)
{
pid->integratState = pid->integratMin;
}
// calculate the integral term

}
