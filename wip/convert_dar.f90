PROGRAM CONVERT_HEPEVT
  !***********************************************************
  !*
  !* Convert /HEPEVT/ event structure to an ASCII file
  !* to be fed by G4HEPEvtInterface
  !*
  !***********************************************************
  PARAMETER (NMXHEP=2000)
  INTEGER :: PLACE,NEVENTS,NEVHEP,NHEP,ISTHEP(NMXHEP), &
       IDHEP(NMXHEP),JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP)
  REAL(8) :: PHEP(5,NMXHEP),VHEP(4,NMXHEP)
  
  
  OPEN(11,FILE='dar_events.hepevt',STATUS='OLD')
  OPEN(12,FILE='dar_events.dat',STATUS='REPLACE')
  NEVENTS = 0
  DO
     READ(11,*,IOSTAT=PLACE),NEVHEP,NHEP
     IF (PLACE < 0) EXIT
     NEVENTS = NEVENTS + 1
     DO IHEP=1,NHEP
        READ(11,*) & 
             ISTHEP(IHEP),IDHEP(IHEP),JMOHEP(1,IHEP),JMOHEP(2,IHEP), &
             JDAHEP(1,IHEP),JDAHEP(2,IHEP),PHEP(1,IHEP),PHEP(2,IHEP), &
             PHEP(3,IHEP),PHEP(4,IHEP),PHEP(5,IHEP),VHEP(1,IHEP), &
             VHEP(2,IHEP),VHEP(3,IHEP),VHEP(4,IHEP)
     ENDDO

     WRITE(12,*) NHEP
     DO IHEP=1,NHEP
        WRITE(12,10) &
             ISTHEP(IHEP),IDHEP(IHEP),JDAHEP(1,IHEP),JDAHEP(2,IHEP), &
             PHEP(1,IHEP),PHEP(2,IHEP),PHEP(3,IHEP),PHEP(5,IHEP) 
10      FORMAT(4I15,4(1X,E15.8))
     ENDDO
  ENDDO
  WRITE(*,*) NEVENTS
  
END PROGRAM CONVERT_HEPEVT
