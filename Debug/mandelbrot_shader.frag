
uniform vec2 U_offset;
uniform vec2 U_scale;
uniform int U_stepsZoom; // aby to nebylo moc bílé pøi zoomování

const vec2 CENTER_OFFSET = vec2(0.5f, 0.5f);

int countSteps(vec2 position, int maxSteps)
{
	vec2 curr = vec2(0, 0);

	for (int i = 1; i <= maxSteps; i++)
	{
		curr = vec2(curr.x * curr.x - curr.y * curr.y, 2 * curr.x * curr.y); // complex square
		curr += position;

		if (length(curr) > 2)
		{
			return i;
		}
	}

	return -1;
}

void main()
{
	vec2 plotPos = (gl_TexCoord[0].xy - CENTER_OFFSET) / U_scale - U_offset;

	int steps = countSteps(plotPos, 100);

	if (steps == -1)
	{
		gl_FragColor = vec4(0.1, 0.1, 0.1, 1);
	}
	else
	{
		float white = 1 - pow(0.9f, clamp(steps - U_stepsZoom, 0, 30));
		gl_FragColor = vec4(white, white, 1, 1);
	}
}
