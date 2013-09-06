<?xml version="1.0" encoding="utf-8"?>

<!-- Copyright (C) 2013 Ridgerun (http://www.ridgerun.com).  -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:preserve-space elements="license" />

<xsl:include href="libutil.xsl" />

<xsl:template match="/components">
	<html>
		<head>
			<title>Software licenses</title>
		</head>
		<body>
			<xsl:for-each select="component">
				<xsl:sort select="translate(name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
				<p>
					<b>
						<a>
							<xsl:attribute name="name">
								<xsl:value-of select="name"/>
							</xsl:attribute>
							<xsl:value-of select="name"/>
							<xsl:text> </xsl:text>
							<xsl:value-of select="version"/>
						</a>
					</b>
				</p>
				<p>
					<b><xsl:text>URL: </xsl:text></b>
					<a>
						<xsl:attribute name="href">
							<xsl:value-of select="link"/>
						</xsl:attribute>
						<xsl:value-of select="link"/>
					</a>
				</p>
				<p>
					<b><xsl:text>License: </xsl:text></b>
					<xsl:call-template name="generate-license-text"/>
				</p>
				<p>
					<!-- b><xsl:text>URL: </xsl:text></b -->
					<xsl:value-of select="summary"/>
				</p>
			</xsl:for-each>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>

