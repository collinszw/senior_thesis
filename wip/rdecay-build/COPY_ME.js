// Use this example configuration file as a starting point for your own files.
{
    seed: 123456, // Random number seed (omit to use time since Unix epoch)

    // Nuclear structure data files
    structure: [ "/usr/share/marley/structure/z019",
		 "/usr/share/marley/structure/z018",
		 "/usr/share/marley/structure/z017", ],

    // Reaction matrix element files
    reactions: [ "/usr/share/marley/react/ve40ArCC_2009.react" ],

    // Neutrino source specification
    source: {
	type: "dar",        // Source spectrum (dar == stopped muon)
	//type: "fd",           // Source spectrum (fd == supernova)
	neutrino: "ve",       // The source produces electron neutrinos
	Emin: 0,              // Minimum neutrino energy (MeV)
	Emax: 60,             // Maximum neutrino energy (MeV)
	temperature: 3.5,     // Temperature (MeV)
	eta: 0                // Pinching parameter (dimensionless, default 0)
    },

    // Incident neutrino direction 3-vector
    direction: { x: 0.0,
		 y: 0.0,
		 z: 1.0
               },

    // Logging configuration
    log: [ { file: "stdout", level: "info" },
           { file: "marley.log", level: "info", overwrite: true } ],

    // Settings for marley command-line executable
    executable_settings: {

	events: 10000, // The number of events to generate

	// Event output configuration
	output: [ { file: "events.ascii", format: "ascii", mode: "overwrite" } ],
    },
}
