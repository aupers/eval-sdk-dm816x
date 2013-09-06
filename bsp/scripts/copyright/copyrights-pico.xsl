<?xml version="1.0" encoding="utf-8"?>

<!-- Copyright (C) 2013 Ridgerun (http://www.ridgerun.com).  -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="libutil.xsl" />

<xsl:preserve-space elements="license" />

<xsl:template match="/components">
	<html>
		<head>
			<title>Software licenses</title>
		</head>
		<body>
			<p>This product contains the following open source software components:</p>
			<xsl:for-each select="component">
				<xsl:sort select="translate(name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
				<xsl:variable name="public">
					<xsl:call-template name="is-license-public">
						<xsl:with-param name="license" select="license/@type" />
					</xsl:call-template>
				</xsl:variable>
				<xsl:if test="$public = 'true'">
					<p>
						<b>
							<xsl:value-of select="name"/>
							<xsl:text> </xsl:text>
							<xsl:value-of select="version"/>
						</b>
						<br/>
						<xsl:value-of select="link"/>
					</p>
					<p/>
				</xsl:if>
			</xsl:for-each>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>

