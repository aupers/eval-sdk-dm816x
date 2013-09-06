<?xml version="1.0" encoding="utf-8"?>

<!-- Copyright (C) 2013 Ridgerun (http://www.ridgerun.com).  -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:preserve-space elements="license" />

<xsl:include href="libutil.xsl" />

<xsl:template match="/components">
	<html>
		<head>
			<title>SOUP software components</title>
		</head>
		<body>
			<xsl:text>This software release uses the following SOUP software components:</xsl:text>
			<ul>
				<xsl:for-each select="component">
					<xsl:sort select="translate(name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
					
					<xsl:variable name="public">
					<xsl:call-template name="is-license-public">
						<xsl:with-param name="license" select="license/@type" />
					</xsl:call-template>
					</xsl:variable>
					<xsl:if test="$public = 'true'">
						<li>
							<b>
								<xsl:value-of select="name"/>
								<xsl:text> </xsl:text>
								<xsl:value-of select="version"/>
							</b><br/>
							<!-- b><xsl:text>URL: </xsl:text></b -->
							<xsl:value-of select="summary"/><br/>
							<xsl:text>URL: </xsl:text>
							<a>
								<xsl:attribute name="href">
									<xsl:value-of select="link"/>
								</xsl:attribute>
								<xsl:value-of select="link"/>
							</a><br/>
							<!-- b><xsl:text>License: </xsl:text></b -->
							<xsl:text>License: </xsl:text>
							<xsl:call-template name="generate-license-link"/>
							<!-- b><xsl:text>Changed: </xsl:text></b -->
							<xsl:if test="changed">
								<xsl:text>Changed: </xsl:text>
								<ul>									
									<xsl:for-each select="changed">
										<li><xsl:value-of select="."/></li>
									</xsl:for-each>
								</ul>
							</xsl:if>
							<!-- b><xsl:text>Issues: </xsl:text></b -->
							<xsl:text>Issues: </xsl:text>
							<xsl:call-template name="generate-issues-text"/><br/>
							<!-- table for off the shelf software documentation -->
							<b><xsl:text>Off-The-Shelf Software Basic Documentation</xsl:text></b>
							<xsl:call-template name="generate-OTS-basic-documentation"/>
						</li>
						<hr/><br/>
					</xsl:if>
				</xsl:for-each>
			</ul>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>

