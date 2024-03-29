    dictionary pimple = mesh.solutionDict().subDict("PIMPLE");

    int nOuterCorr(readInt(pimple.lookup("nOuterCorrectors")));
    int nCorr(readInt(pimple.lookup("nCorrectors")));

    int nNonOrthCorr =
        pimple.lookupOrDefault<int>("nNonOrthogonalCorrectors", 0);

	[[maybe_unused]]  bool momentumPredictor =
		pimple.lookupOrDefault<Switch>("momentumPredictor", true);

	[[maybe_unused]]  bool transonic =
		pimple.lookupOrDefault<Switch>("transonic", false);
