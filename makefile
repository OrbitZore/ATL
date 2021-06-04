all: Document/Document.md Document/Document.pdf
Document/Document.md: base/include/*.hpp
	cd base/include && \
	for i in *.hpp; do \
		echo "# $$i"; \
		echo ; \
		echo \`\`\`cpp; \
		cat "$$i"; \
		echo ; \
		echo \`\`\`; \
		echo; \
	done > ../../Document/Document.md
Document/Document.pdf: Document/Document.md
	pandoc -s \
	--pdf-engine=xelatex \
	--toc \
	-H Document/header.latex \
	Document/Document.md -o Document/Document.pdf
clean:
	rm Document/Document.pdf Document/Document.md