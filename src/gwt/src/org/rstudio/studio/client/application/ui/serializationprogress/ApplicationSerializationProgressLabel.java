/*
 * ApplicationSerializationProgressLabel.java
 *
 * Copyright (C) 2009-19 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant
 * to the terms of a commercial license agreement with RStudio, then
 * this program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */
package org.rstudio.studio.client.application.ui.serializationprogress;

import com.google.gwt.core.client.GWT;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Widget;
import org.rstudio.core.client.a11y.A11y;

public class ApplicationSerializationProgressLabel extends Composite
{
   interface MyBinder
         extends UiBinder<Widget, ApplicationSerializationProgressLabel>
   {}
   private static MyBinder binder = GWT.create(MyBinder.class);

   public ApplicationSerializationProgressLabel()
   {
      initWidget(binder.createAndBindUi(this));
      A11y.setStatusRole(label_, false);
   }

   public void setText(String text)
   {
      label_.setText(text);
   }

   @UiField
   Label label_;
}
