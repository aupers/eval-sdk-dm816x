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
			<p>This product contains the following open source software components:</p>
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
							<a>
								<xsl:attribute name="href">
									<xsl:text>#</xsl:text><xsl:value-of select="name"/>
								</xsl:attribute>
								<xsl:value-of select="name"/>
								<xsl:text> </xsl:text>
								<xsl:value-of select="version"/>
							</a>
						</li>
					</xsl:if>
				</xsl:for-each>
			</ul>
			<p>Please see below for license details:</p>
			<xsl:for-each select="component">
				<xsl:sort select="translate(name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
				<xsl:variable name="public">
					<xsl:call-template name="is-license-public">
						<xsl:with-param name="license" select="license/@type" />
					</xsl:call-template>
				</xsl:variable>
				<xsl:if test="$public = 'true'">
					<hr/>
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
						<!-- b><xsl:text>URL: </xsl:text></b -->
						<xsl:value-of select="summary"/>
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
					<!-- b><xsl:text>Issues: </xsl:text></b -->
					<xsl:if test="normalize-space( issues ) != ''">
						<p>
							<b><xsl:text>Issues: </xsl:text></b>
							<xsl:call-template name="generate-issues-text"/><br/>
							<!--
							<b><xsl:text>Issues: </xsl:text></b>
							<a>
								<xsl:attribute name="href">
									<xsl:value-of select="issues"/>
								</xsl:attribute>
								<xsl:value-of select="issues"/>
							</a><br/>
							-->
						</p>
					</xsl:if>
					<!-- b><xsl:text>Changed: </xsl:text></b -->
					<xsl:if test="changed">
						<b><xsl:text>Changed: </xsl:text></b>
						<ul>									
							<xsl:for-each select="changed">
								<li><xsl:value-of select="."/></li>
							</xsl:for-each>
						</ul>
					</xsl:if>
					<!-- b><xsl:text>License: </xsl:text></b -->
					<p>
						<b><xsl:text>License: </xsl:text></b>
						<xsl:call-template name="generate-license-link"/>
					</p>										
					<p>
						<!--xsl:value-of select="translate(
							 normalize-space(
							  translate(license/., '&#xA;&#xD;', '&#xA0;&#xAD;')
							 ), '&#xA0;&#xAD;­', '&#xA;&#xD;'
							)
							"/ -->
						<xsl:call-template name="add-line-breaks">
							<xsl:with-param name="string" select="license/text" />
						</xsl:call-template>
						<!-- xsl:value-of select="license"/ -->
					</p>
				</xsl:if>
			</xsl:for-each>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>

