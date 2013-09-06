<?xml version="1.0" encoding="utf-8"?>

<!-- Copyright (C) 2013 Ridgerun (http://www.ridgerun.com).  -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template name="add-line-breaks">
	<xsl:param name="string" select="." />
	<xsl:choose>
		<xsl:when test="contains($string, '&#xA;')">
			<xsl:value-of select="substring-before($string, '&#xA;')" />
				<br/>
			<xsl:call-template name="add-line-breaks">
				<xsl:with-param name="string" select="substring-after($string, '&#xA;')" />
			</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="$string" />
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<!-- check if license is public -->
<xsl:template name="is-license-public">
	<xsl:param name="license" />
	<xsl:choose>
		<xsl:when test="$license = 'KS'">
			<xsl:value-of select="false()"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="true()"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<!-- generate issue text -->
<xsl:template name="generate-issues-text">
	<xsl:param name="string" select="." />
	<xsl:if test="(normalize-space( issues/link ) != '')">
	<a>
		<xsl:attribute name="href">
			<xsl:value-of select="issues/link"/>
		</xsl:attribute>
		<xsl:value-of select="issues/link"/>
	</a><br/>
	</xsl:if>
	<xsl:if test="(normalize-space( issues/remark ) != '')">
	<xsl:value-of select="issues/remark"/><br/>
	</xsl:if>
</xsl:template>

<!-- generate license link -->
<xsl:template name="generate-license-link">
	 <xsl:choose>
        <xsl:when test="substring(license/@type, string-length(license/@type)-1) = '_p'">
        <a>
			<xsl:attribute name="href">
				<xsl:value-of select="license/link"/>
			</xsl:attribute>
			<xsl:value-of select="concat(substring(license/@type, 0, string-length(license/@type)-1),'+')"/>
		</a><br/>
        </xsl:when>
        <xsl:otherwise>
      		<a>
				<xsl:attribute name="href">
					<xsl:value-of select="license/link"/>
				</xsl:attribute>
				<xsl:value-of select="license/@type"/>
			</a><br/>
        </xsl:otherwise>
      </xsl:choose>
</xsl:template>

<!-- generate license text -->
<xsl:template name="generate-license-text">
	 <xsl:choose>
        <xsl:when test="substring(license/@type, string-length(license/@type)-1) = '_p'">
			<xsl:value-of select="concat(substring(license/@type, 0, string-length(license/@type)-1),'+')"/><br/>
        </xsl:when>
        <xsl:otherwise>
			<xsl:value-of select="license/@type"/><br/>
        </xsl:otherwise>
      </xsl:choose>
</xsl:template>

<!-- generate OTS basic information as many as possible -->
<xsl:template name="generate-OTS-basic-documentation">
	<table border="1">	
		<colgroup>
			<col width="400"/>
		</colgroup>
		<tr>
			<td align="left" valign="top">
				<xsl:text>
				Question 1: What is it? Please highlight the title and manufacturer, version level, release date, patch number and upgrade
				designation for the OTS software. Also show why this OTS SW is appropriate for this device and will any documentation be provided to 
				the end user. Are there any design limitations of this OTS SW?
				</xsl:text>
			</td>
			<td align="left" valign="top">
				<xsl:text>Title: </xsl:text>
				<xsl:value-of select="name"/><br/>
				<xsl:text>Manufacturer: </xsl:text>
				<xsl:value-of select="manufacturer"/><br/>
				<xsl:text>Version: </xsl:text>
				<xsl:value-of select="version"/><br/>
				<xsl:if test="releaseDate">
				<xsl:text>Release Date: </xsl:text>
					<xsl:value-of select="releaseDate"/><br/><br/>
				</xsl:if>
				<xsl:text>Description: </xsl:text><br/>
				<xsl:value-of select="summary"/><br/><br/>
				<xsl:text>Documentation: </xsl:text><br/>
				<xsl:text>There will be no documentation provided to the user, because the end user doesn’t interact with OTS software directly.</xsl:text>
			</td>
		</tr>
		<tr>
			<td align="left" valign="top">
				<xsl:text>
				Question 2: Please illustrate the Electrical and the Software specification of the computer system for which this OTS SW is validated.
				</xsl:text>
			</td>
			<td align="left" valign="top">
				<font color="red" size="4">
				<xsl:text>/Insert here reference to product specific SW and HW requirements/</xsl:text>
				</font>
			</td>
		</tr>
		<tr>
			<td align="left" valign="top">
				<xsl:text>
				Question 3: What aspects of the OTS SW needs to be installed/configured? What steps are required and how often is the configuration 
				is changed? What training and education is required for the user? How does the manufacturer ensure that non-specified OTS SW is not 
				introduced into the medical device?
				</xsl:text>
			</td>
			<td align="left" valign="top">
				<xsl:text>
				The software is preinstalled during production process. Nothing can be configured or installed by the end user. 
				There is no possibilities for the end user to to see, remove or change the OTS software.
				</xsl:text>
			</td>
		</tr>
		<tr>
			<td align="left" valign="top">
				<xsl:text>
				Question 4: What functions does the OTS SW provide in this device? Please provide the SRS for this OTS SW and also make 
				sure it illustrates any interaction with SW outside this device.
				</xsl:text>
			</td>
			<td align="left" valign="top">
				<font color="red" size="4">
				<xsl:text>/Insert here reference to product specific SW requirements and / or design documentation/</xsl:text>
				</font>
			</td>
		</tr>
		<tr>
			<td align="left" valign="top">
				<xsl:text>
				<![CDATA[
				Question 5: Please provide V&V test  data and any bugs list for the OTS SW. Please make sure testing of the device should 
				be done after the OTS SW has been incorporated in it.
				]]>
				</xsl:text>
			</td>
			<td align="left" valign="top">
				<xsl:text>
				The Software can not be used for it's own. It is part of the application program, so no separate software test of the OTS software itself has to be done.
				The tests of the application program are documented in test reports:
				</xsl:text><br/>
				<font color="red" size="4">
					<xsl:text>/Insert here reference to product specific test reports/</xsl:text><br/><br/>
				</font>
				<xsl:text>An actual list of current known OTS software problems can be found here:</xsl:text><br/>
				<xsl:call-template name="generate-issues-text"/>
			</td>
		</tr>
		<tr>
			<td align="left" valign="top">
				<xsl:text>
				Question 6: What steps have been taken to ensure that incorrect versions of the OTS SW are not installed on the device? How 
				will you maintain the OTS SW configuration and correct installation process? How will you maintain and provide life cycle support 
				for the OTS SW?
				</xsl:text>
			</td>
			<td align="left" valign="top">
				<xsl:text>
				The OTS software is part of a application program. This is maintained by the software developer only. There is no possibility to install the OTS 
				software separately from the application program. The OTS software configuration and installation procedures are included in the 
				source code management. Updates of the OTS software are evaluated in the development department. As with any device software 
				change, newer OTS software always results in subsequent test phases and a release procedure according to the Storz SOPs.
				</xsl:text>
			</td>
		</tr>
	</table>
</xsl:template>

</xsl:stylesheet>

