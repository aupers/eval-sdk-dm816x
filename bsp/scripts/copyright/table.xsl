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
			<table border="1">
				<tr>
					<th>Component</th>
					<th>Version</th>
					<th>License</th>
					<th>URL</th>
					<th>Issues</th>
					<th>Changed</th>
				</tr>
				<xsl:for-each select="component">
					<xsl:sort select="translate(name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
					<tr>
						<td>
							<xsl:value-of select="name"/>
							<xsl:text> </xsl:text>
							<xsl:value-of select="version"/>
						</td>
						<td>
							<xsl:value-of select="version"/>
						</td>
						<td>
							<xsl:call-template name="generate-license-link"/>
						</td>
						<td>
							<a>
								<xsl:attribute name="href">
									<xsl:value-of select="link"/>
								</xsl:attribute>
								<xsl:value-of select="link"/>
							</a>
						</td>
						<td>
							<xsl:call-template name="generate-issues-text"/>
							<!--a>
								<xsl:attribute name="href">
									<xsl:value-of select="issues"/>
								</xsl:attribute>
								<xsl:value-of select="issues"/>
							</a-->
						</td>
						<td>
							<xsl:for-each select="changed">
								<xsl:value-of select="."/><br/>
							</xsl:for-each>
						</td>
					</tr>
				</xsl:for-each>
			</table>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>

