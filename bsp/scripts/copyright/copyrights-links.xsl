<?xml version="1.0" encoding="utf-8"?>

<!-- Copyright (C) 2013 Ridgerun (http://www.ridgerun.com).  -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text"/>

<xsl:template match="/components">
	<xsl:for-each select="component">
		<xsl:value-of select="link"/><xsl:text>&#10;</xsl:text>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>

