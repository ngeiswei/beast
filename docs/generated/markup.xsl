<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" indent="no"/>

  <xsl:param name="revision"/>

  <xsl:template match="texinfo">
    <!-- basic tag definitions -->
    <tagdef name="bold"           weight="bold" stretch="expanded" />
    <tagdef name="italic"         style="italic" />
    <tagdef name="mono"           family="mono" />
    <tagdef name="center"         justification="center" />
    <tagdef name="fill"           justification="fill" />
    <tagdef name="underline"      underline="single" />
    <tagdef name="doubleline"     underline="double" />
    <tagdef name="fg-black"       foreground="#000000" />
    <tagdef name="fg-white"       foreground="#ffffff" />
    <tagdef name="fg-red"         foreground="#ff0000" />
    <tagdef name="fg-green"       foreground="#00ff00" />
    <tagdef name="fg-blue"        foreground="#0000ff" />
    <tagdef name="fg-turquoise"   foreground="#00ffff" />
    <tagdef name="fg-pink"        foreground="#ff00ff" />
    <tagdef name="fg-yellow"      foreground="#ffff00" />
    <tagdef name="bg-black"       background="#000000" />
    <tagdef name="bg-white"       background="#ffffff" />
    <tagdef name="bg-red"         background="#ff0000" />
    <tagdef name="bg-green"       background="#00ff00" />
    <tagdef name="bg-blue"        background="#0000ff" />
    <tagdef name="bg-turquoise"   background="#00ffff" />
    <tagdef name="bg-pink"        background="#ff00ff" />
    <tagdef name="bg-yellow"      background="#ffff00" />
    <!-- lower priority tags need to come first -->
    <tagdef name="section"        indent="0" />
    <tagdef name="subsection"     indent="0" />
    <tagdef name="subsubsection"  indent="0" />
    <tagdef name="body"           wrap_mode="word" left_margin="5" right_margin="5" />
    <tagdef name="indent-margin"  left_margin="20" right_margin="20" />
    <tagdef name="item-margin"    left_margin="18" />
    <tagdef name="bullet-tag"     indent="-10" />
    <tagdef name="dline"          underline="double" weight="bold" />
    <tagdef name="sline"          underline="single" weight="bold" />
    <tagdef name="nowrap"         wrap_mode="none" />
    <tagdef name="indented"	  left_margin="20" />
    <tagdef name="tableterm"	  family="mono"/>
    <tagdef name="tableitem"	  indent="45" />
    <tagdef name="multitable"     family="mono" />

    <!-- contextual tags -->
    <tagdef name="code"           family="mono" foreground="#000040" />

    <tagdef name="acronym"        />
    <tagdef name="cite"           />
    <tagdef name="command"        />
    <tagdef name="dfn"            />
    <tagdef name="email"          />
    <tagdef name="env"            />
    <tagdef name="file"           />
    <tagdef name="kbd"            />
    <tagdef name="key"            />
    <tagdef name="option"         />
    <tagdef name="samp"           />
    <tagdef name="strong"         weight="bold" />
    <tagdef name="url"            />
    <tagdef name="var"            />

    <tagdef name="revision"       style="italic" />

    <tagdef name="programlisting" family="mono" wrap_mode="none" foreground="#000040" />
    <tagdef name="property"       style="italic" />
    <tagdef name="channel"        style="italic" />
    <tagdef name="menupath"       style="italic" weight="bold" background="#e0e0e0" />
    <tagdef name="pagepath"       style="italic" weight="bold" background="#f0f0f0" />
    <tagdef name="object"         family="mono" style="italic" />
    <span tag="body">
      <xsl:apply-templates/>

      <xsl:call-template name="revision"/>
      <breakline/>
      <newline/>
    </span>
  </xsl:template>

  <!-- useless tags -->
  <xsl:template match="setfilename|settitle|itemfunction|columnfraction"/>

  <!-- revision bit -->
  <xsl:template name="revision">
    <xsl:if test="string-length($revision) > 0">
      <breakline/>
      <newline/>
      <span tag="revision">
        <xsl:text>Document revised: </xsl:text><xsl:value-of select="$revision"/>
      </span>
      <breakline/>
      <newline/>
    </xsl:if>
  </xsl:template>

  <!-- table of contents related ftuff -->
  <xsl:template name="node_number">
    <xsl:text>node-</xsl:text><xsl:number level="multiple" count="chapter|section|subsection|subsubsection|appendix|appendixsec|appendixsubsec|appendixsubsubsec|unnumbered|unnumberedsec|unnumberedsubsec|unnumberedsubsubsec" format="1-1-1-1"/>
  </xsl:template>

  <xsl:template match="table-of-contents">
    <newline/><breakline/>
    <newline/><breakline/>
    <span tag="dline">
      <span tag="center">
	<xsl:text>Table Of Contents</xsl:text>
      </span>
    </span>
    <newline/><breakline/>
    <newline/><breakline/>

    <xsl:for-each select="/texinfo/chapter|/texinfo/unnumbered|/texinfo/appendix">
      <xsl:if test="local-name() = 'chapter'">
	<xsl:call-template name="toc_chapter"/>
      </xsl:if>
      <xsl:if test="local-name() = 'unnumbered'">
	<!-- <xsl:call-template name="toc_unnumbered"/> -->
      </xsl:if>
      <xsl:if test="local-name() = 'appendix'">
	<!-- <xsl:call-template name="toc_appendix"/> -->
      </xsl:if>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="toc_chapter">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number format="1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./section) > 0">
      <span tag="indented">
	<xsl:for-each select="./section">
	  <xsl:call-template name="toc_section"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_section">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number level="multiple" count="chapter|section" format="1.1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./subsection) > 0">
      <span tag="indented">
	<xsl:for-each select="./subsection">
	  <xsl:call-template name="toc_subsection"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_subsection">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number level="multiple" count="chapter|section|subsection" format="1.1.1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./subsubsection) > 0">
      <span tag="indented">
	<xsl:for-each select="./subsubsection">
	  <xsl:call-template name="toc_subsubsection"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_subsubsection">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number level="multiple" count="chapter|section|subsection|subsubsection" format="1.1.1.1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
  </xsl:template>

  <xsl:template name="toc_appendix">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:text>Appendix </xsl:text><xsl:number format="A - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./appendixsec) > 0">
      <span tag="indented">
	<xsl:for-each select="./appendixsec">
	  <xsl:call-template name="toc_appendixsec"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_appendixsec">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number level="multiple" count="appendix|appendixsec" format="A.1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./appendixsubsec) > 0">
      <span tag="indented">
	<xsl:for-each select="./appendixsubsec">
	  <xsl:call-template name="toc_appendixsubsec"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_appendixsubsec">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number level="multiple" count="appendix|appendixsec|appendixsubsec" format="A.1.1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./appendixsubsubsec) > 0">
      <span tag="indented">
	<xsl:for-each select="./appendixsubsubsec">
	  <xsl:call-template name="toc_appendixsubsubsec"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_appendixsubsubsec">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:number level="multiple" count="appendix|appendixsec|appendixsubsec|appendixsubsubsec" format="A.1.1.1 - "/><xsl:value-of select="title"/>
    </activatable><breakline/>
  </xsl:template>

  <xsl:template name="toc_unnumbered">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./unnumberedsec) > 0">
      <span tag="indented">
	<xsl:for-each select="./unnumberedsec">
	  <xsl:call-template name="toc_unnumberedsec"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_unnumberedsec">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./unnumberedsubsec) > 0">
      <span tag="indented">
	<xsl:for-each select="./unnumberedsubsec">
	  <xsl:call-template name="toc_unnumberedsubsec"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_unnumberedsubsec">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:value-of select="title"/>
    </activatable><breakline/>
    <xsl:if test="count(./unnumberedsubsubsec) > 0">
      <span tag="indented">
	<xsl:for-each select="./unnumberedsubsubsec">
	  <xsl:call-template name="toc_unnumberedsubsubsec"/>
	</xsl:for-each>
      </span>
    </xsl:if>
  </xsl:template>

  <xsl:template name="toc_unnumberedsubsubsec">
    <activatable>
      <xsl:attribute name="data">
	<xsl:text>#</xsl:text><xsl:call-template name="node_number"/>
      </xsl:attribute>
      <xsl:value-of select="title"/>
    </activatable><breakline/>
  </xsl:template>

  <!-- end of table of contents related ftuff -->

  <xsl:template match="linebreak">
    <newline/>
  </xsl:template>

  <xsl:template match="section|appendixsec|unnumberedsec">
    <span tag="section">
      <xsl:apply-templates/>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="subsection|appendixsubsec|unnumberedsubsec">
    <span tag="subsection">
      <xsl:apply-templates/>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="subsubsection|appendixsubsubsec|unnumberedsubsubsec">
    <span tag="subsubsection">
      <xsl:apply-templates/>
    </span>
    <breakline/>
  </xsl:template>

  <!-- title ftuff -->

  <xsl:template match="chapter/title">
    <breakline/>
    <newline/>
    <newline/>
    <span tag="dline">
      <span tag="center">
	<xsl:number count="chapter" format="1 - "/><xsl:apply-templates/>
	<breakline/>
      </span>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="section/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:number level="multiple" count="chapter|section" format="1.1 - "/><xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="subsection/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:number level="multiple" count="chapter|section|subsection" format="1.1.1 - "/><xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="subsubsection/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:number level="multiple" count="chapter|section|subsection|subsubsection" format="1.1.1.1 - "/><xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="appendix/title">
    <breakline/>
    <newline/>
    <newline/>
    <span tag="dline">
      <span tag="center">
	<xsl:number count="appendix" format="A - "/><xsl:apply-templates/>
	<breakline/>
      </span>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="appendixsec/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:number level="multiple" count="appendix|appendixsec" format="A.1 - "/><xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="appendixsubsec/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:number level="multiple" count="appendix|appendixsec|appendixsubsec" format="A.1.1 - "/><xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="appendixsubsubsec/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:number level="multiple" count="appendix|appendixsec|appendixsubsec|appendixsubsubsec" format="A.1.1.1 - "/><xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="unnumbered/title|chapheading/title/majorheading/title">
    <breakline/>
    <newline/>
    <newline/>
    <span tag="dline">
      <span tag="center">
	<xsl:apply-templates/>
	<breakline/>
      </span>
    </span>
    <newline/>
  </xsl:template>

  <xsl:template match="unnumberedsec/title|unnumberedsubsec/title|unnumberedsubsubsec/title|heading/title|subheading/title|subsubheading/title">
    <breakline/>
    <newline/>
    <span tag="sline">
      <xsl:apply-templates/>
      <breakline/>
    </span>
    <newline/>
  </xsl:template>

  <!-- title ftuff ends here -->

  <xsl:template match="code">
    <span tag="code">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="preformat">
    <breakline/>
    <span tag="nowrap">
      <span tag="mono">
	<keep-space><xsl:apply-templates/></keep-space>
      </span>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="keepspace">
    <breakline/>
    <span tag="nowrap">
      <keep-space><xsl:apply-templates/></keep-space>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="para">
    <!-- <breakline/> -->
    <xsl:apply-templates/>
    <!-- <breakline/> -->
  </xsl:template>

  <xsl:template match="acronym|cite|dfn|kbd|samp|var|strong|url|email|key|env|file|command|option">
    <span>
      <xsl:attribute name="tag">
	<xsl:value-of select="local-name()"/>
      </xsl:attribute>
      <span tag="code">
	<xsl:apply-templates/>
      </span>
    </span>
  </xsl:template>

  <xsl:template match="programlisting">
    <breakline/>
    <span tag="programlisting">
      <keep-space><xsl:apply-templates/></keep-space>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="menupath">
    <span tag="menupath">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="pagepath">
    <span tag="pagepath"><xsl:apply-templates/></span>
  </xsl:template>

  <xsl:template match="property">
    <span tag="property">
      "<xsl:apply-templates/>"
    </span>
  </xsl:template>

  <xsl:template match="object">
    <span tag="object">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="module">
    <span tag="object">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="channel">
    <span tag="channel">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="emph|emphasize">
    <span tag="italic">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="important">
    <span style="italic">
      <span tag="underline">
	<xsl:apply-templates/>
      </span>
    </span>
  </xsl:template>

  <xsl:template match="center">
    <breakline/>
    <span tag="center">
      <xsl:apply-templates/>
      <breakline/>
    </span>
  </xsl:template>

  <xsl:template match="indent">
    <breakline/>
    <span tag="indent-margin">
      <xsl:apply-templates/>
      <breakline/>
    </span>
  </xsl:template>

  <xsl:template match="fill">
    <breakline/>
    <!-- grumbl, text-widget fill is not implemented -->
    <keep-space><xsl:apply-templates/></keep-space><breakline/>
  </xsl:template>

  <xsl:template match="itemize|enumerate">
    <breakline/>
    <xsl:apply-templates/>
    <breakline/>
  </xsl:template>

  <xsl:template match="itemize/item">
    <breakline/>
    <span tag="item-margin">
      <span tag="bullet-tag"><image stock="gtk-yes" size="10x10"/></span>
      <xsl:apply-templates/>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="enumerate/item">
    <breakline/>
    <span tag="item-margin">
      <span tag="bullet-tag"><xsl:number format="1. "/></span>
      <xsl:apply-templates/>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="uref">
    <span tag="fg-blue">
      <span tag="underline">
	<activatable>
	  <xsl:attribute name="data">
	    <xsl:value-of select="urefurl"/>
	  </xsl:attribute>
	  <xsl:choose>
	    <xsl:when test="count(child::urefreplacement)"><xsl:apply-templates select="urefreplacement"/></xsl:when>
	    <xsl:when test="count(child::urefdesc)"><xsl:apply-templates select="urefdesc"/> (<xsl:apply-templates select="urefurl"/>)</xsl:when>
	    <xsl:otherwise><xsl:apply-templates select="urefurl"/></xsl:otherwise>
	  </xsl:choose>
	</activatable>
      </span>
    </span>
  </xsl:template>

  <xsl:template match="image">
    <activatable data="ImageClick">
      <image>
	<xsl:attribute name="file">
	  <xsl:value-of select="."/>.<xsl:value-of select="@extension"/>
	</xsl:attribute>
	[<xsl:value-of select="@alttext"/>]
      </image>
    </activatable>
  </xsl:template>

  <!-- omit indices for a while -->
  <xsl:template match="indexterm|printindex">
  </xsl:template>

  <xsl:template match="tableterm">
    <span tag="tableterm">
      <xsl:apply-templates/>
    </span>
    <breakline/>
  </xsl:template>

  <xsl:template match="tableitem/item/para">
    <span tag="tableitem">
      <xsl:apply-templates/>
    </span>
    <breakline/>
    <newline/>
  </xsl:template>

  <xsl:template match="multitable">
    <span tag="multitable">
      <xsl:apply-templates/>
    </span>
  </xsl:template>

  <xsl:template match="multitable/row">
    <xsl:apply-templates/>
    <breakline/>
  </xsl:template>

</xsl:stylesheet>
