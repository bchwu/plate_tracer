static int fix_t1 = 0

case 8:  /* read plate id */
    if (fix_t1 == 1 && E->boundary.fix_init_age == 1)
        return;
 
    fix_t1 = 1;
 
    sprintf(output_file1,"%s.%d_velocity_%0.2fMa.xy",E->viscosity.plate_id_filename, cap, newage1);
    fp1=fopen(output_file1,"r");
    if (fp1 == NULL) {
        fprintf(E->fp,"(Problem_related #case8_1) Cannot open %s\n",output_file1);
        exit(8);
    }
 
    if((E->parallel.me==0) && (output==1))   {
        fprintf(E->fp,"PlateId: Starting Age = %g, Elapsed time = %g, Current Age = %g\n",E->control.start_age,E->monitor.elapsed_time,age);
        fprintf(E->fp,"PlateId: File = %s\n",output_file1);
        fprintf(E->fp, "newage1 = %.1f\n", newage1);
    }
 
    /* plate id assignment */
    nnn=nox*noy;
    iVB=(int*) malloc ((nnn+1)*sizeof(int));
    for(i=1;i<=nnn;i++)   {
        fgets(buffer, 255, fp1);
        if (sscanf(buffer, "%f %f %f %f %d", &fjunk0, &fjunk1, &fjunk2, &fjunk3, &(iVB[i])) != 5) {
            fprintf(stderr, "Error while reading file '%s'\n", output_file1);
            exit(8);
        }
    }
 
    if(E->parallel.me_loc[3]==E->parallel.nprocz-1 )  {
        for(k=1;k<=noy1;k++)
            for(i=1;i<=nox1;i++)    {
                nodeg = E->lmesh.nxs+i-1 + (E->lmesh.nys+k-2)*nox;
                nodel = (k-1)*nox1 + i;
                E->slice.surf_Pid[m][nodel] = iVB[nodeg];
            }
        }
     /* end */
    fclose(fp1);
break;
/* end of case 8 */
