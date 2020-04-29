void FFT(unsigned int logN, double* real, double* im) // logN is base 2 log(N)
{
	unsigned int n = 0, nspan, span, submatrix, node;
	unsigned int N = 1 << logN;
	double temp, primitive_root, angle, realtwiddle, imtwiddle;



	for (span = N >> 1; span; span >>= 1)      // loop over the FFT stages
	{
		primitive_root = MINPI / span;     // define MINPI in the header

		for (submatrix = 0; submatrix < (N >> 1) / span; submatrix++)
		{
			for (node = 0; node < span; node++)
			{
				nspan = n + span;
				temp = real[n] + real[nspan];       // additions & subtractions
				real[nspan] = real[n] - real[nspan];
				real[n] = temp;
				temp = im[n] + im[nspan];
				im[nspan] = im[n] - im[nspan];
				im[n] = temp;

				angle = primitive_root * node;      // rotations
				realtwiddle = cos(angle);
				imtwiddle = sin(angle);
				temp = realtwiddle * real[nspan] - imtwiddle * im[nspan];
				im[nspan] = realtwiddle * im[nspan] + imtwiddle * real[nspan];
				real[nspan] = temp;

				n++;   // not forget to increment n

			} // end of loop over nodes

			n = (n + span) & (N - 1);   // jump over the odd blocks

		} // end of loop over submatrices

	} // end of loop over FFT stages
} // end of FFT function
