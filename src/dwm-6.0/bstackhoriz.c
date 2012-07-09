static void
bstackhoriz(Monitor *m) {
	int w, mh, mx, tx, ty, th;
	unsigned int i, n;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	if(n > m->nmaster) {
		mh = m->nmaster ? m->mfact * m->wh : 0;
		th = (m->wh - mh) / (n - m->nmaster);
		ty = m->wy + mh;
	} 
	else {
		th = mh = m->wh;
		ty = m->wy;
	}
	for(i = mx = 0, tx = m->wx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if(i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - (2 * c->bw), mh - (2 * c->bw), False);
			mx += WIDTH(c);
		} 
		else {
			resize(c, tx, ty, m->ww - (2 * c->bw), th - (2 * c->bw), False);
			if(th != m->wh)
				ty += HEIGHT(c);
		}
	}
}
