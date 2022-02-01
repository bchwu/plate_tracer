Workflow of the palte tracking procedure

1. Data preparation
   Export the plateIDs from any reconstruction model with a time interval of 1 Myr using the GPlates software.
   In GPlates: Export... -> Add Export... -> Velocities -> GMT(*.xy)
   Export Description/Velocities will be exported as:
   domain_point_lon domain_point_lat velocity_azimuth velocity_magnitude plate_id
   Only the fifth column will be used.
   
2. Read in plateIDs from files
   Add a new switch case to function full_read_input_files_for_timesteps() in CitcomS/lib/Full_read_input_from_files.c
   
3. Initialize the plate tracer flavors
   Add a new function init_plate_tracer_flavors() to CitcomS/lib/Tracer_setup.c
   
Example(settings in the inputfile):
plate_tracer=on
PLATE=919,101,901,926,902
tracer_flavors=7 # 0 for normal mantle, 1 for the CMB chemical layer, 2~6 for the plates above
buoyancy_ratio=0.5,0.0,0.0,0.0,0.0,0.0
