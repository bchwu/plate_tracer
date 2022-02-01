void init_plate_tracer_flavors(struct All_variables *E)
{
    int j, kk, number_of_tracers;
    int i, id_temp;
    double flavor;
    double rad;
 
    /* get plateids */
    full_read_input_files_for_timesteps(E,8,1);
 
    for (j=1;j<=E->sphere.caps_per_proc;j++) {
        number_of_tracers = E->trace.ntracers[j];

        for (kk=1;kk<=number_of_tracers;kk++) {
            rad = E->trace.basicq[j][2][kk];

            if (rad > (1.0 - E->viscosity.zlith)) {
                id_temp = E->slice.surf_Pid[j][(E->ien[j][E->trace.ielement[j][kk]].node[7] - 1) / E->lmesh.noz + 1];
 
                for (i=0; i<E->trace.nflavors-2; i++)
                    if (id_temp == E->trace.PLATE[i])
					    E->trace.extraq[j][0][kk] = (double)(i+2);

            }
        }
    }
 
    return;
}

