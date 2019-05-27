namespace ConnectDB
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.grpBoxView = new System.Windows.Forms.GroupBox();
            this.txtBoxEmployeeID = new System.Windows.Forms.TextBox();
            this.lbEmployeeID = new System.Windows.Forms.Label();
            this.btnView = new System.Windows.Forms.Button();
            this.grpBoxContent = new System.Windows.Forms.GroupBox();
            this.txtPhoneNumber = new System.Windows.Forms.TextBox();
            this.txtEmail = new System.Windows.Forms.TextBox();
            this.txtCommisionPCT = new System.Windows.Forms.TextBox();
            this.txtSalary = new System.Windows.Forms.TextBox();
            this.txtDepartmentID = new System.Windows.Forms.TextBox();
            this.txtManagerID = new System.Windows.Forms.TextBox();
            this.txtJobID = new System.Windows.Forms.TextBox();
            this.txtHireDate = new System.Windows.Forms.TextBox();
            this.txtLastName = new System.Windows.Forms.TextBox();
            this.txtFirstName = new System.Windows.Forms.TextBox();
            this.lbCommisionPCT = new System.Windows.Forms.Label();
            this.lbDepartmentID = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lbJobID = new System.Windows.Forms.Label();
            this.lbSalary = new System.Windows.Forms.Label();
            this.lbManagerID = new System.Windows.Forms.Label();
            this.lbEmail = new System.Windows.Forms.Label();
            this.lbHireDate = new System.Windows.Forms.Label();
            this.lbLastName = new System.Windows.Forms.Label();
            this.lbFirstName = new System.Windows.Forms.Label();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnSearchAll = new System.Windows.Forms.Button();
            this.listAllEmployees = new System.Windows.Forms.ListView();
            this.grpBoxView.SuspendLayout();
            this.grpBoxContent.SuspendLayout();
            this.SuspendLayout();
            // 
            // grpBoxView
            // 
            this.grpBoxView.Controls.Add(this.txtBoxEmployeeID);
            this.grpBoxView.Controls.Add(this.lbEmployeeID);
            this.grpBoxView.Controls.Add(this.btnView);
            this.grpBoxView.Location = new System.Drawing.Point(13, 13);
            this.grpBoxView.Name = "grpBoxView";
            this.grpBoxView.Size = new System.Drawing.Size(764, 88);
            this.grpBoxView.TabIndex = 0;
            this.grpBoxView.TabStop = false;
            this.grpBoxView.Text = "[조회]";
            // 
            // txtBoxEmployeeID
            // 
            this.txtBoxEmployeeID.Location = new System.Drawing.Point(110, 42);
            this.txtBoxEmployeeID.Name = "txtBoxEmployeeID";
            this.txtBoxEmployeeID.Size = new System.Drawing.Size(252, 21);
            this.txtBoxEmployeeID.TabIndex = 2;
            // 
            // lbEmployeeID
            // 
            this.lbEmployeeID.AutoSize = true;
            this.lbEmployeeID.Location = new System.Drawing.Point(19, 45);
            this.lbEmployeeID.Name = "lbEmployeeID";
            this.lbEmployeeID.Size = new System.Drawing.Size(85, 12);
            this.lbEmployeeID.TabIndex = 1;
            this.lbEmployeeID.Text = "Employee ID :";
            // 
            // btnView
            // 
            this.btnView.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.btnView.Location = new System.Drawing.Point(635, 31);
            this.btnView.Name = "btnView";
            this.btnView.Size = new System.Drawing.Size(111, 40);
            this.btnView.TabIndex = 0;
            this.btnView.Text = "조회";
            this.btnView.UseVisualStyleBackColor = true;
            this.btnView.Click += new System.EventHandler(this.BtnView_Click);
            // 
            // grpBoxContent
            // 
            this.grpBoxContent.Controls.Add(this.txtPhoneNumber);
            this.grpBoxContent.Controls.Add(this.txtEmail);
            this.grpBoxContent.Controls.Add(this.btnOK);
            this.grpBoxContent.Controls.Add(this.txtCommisionPCT);
            this.grpBoxContent.Controls.Add(this.txtSalary);
            this.grpBoxContent.Controls.Add(this.txtDepartmentID);
            this.grpBoxContent.Controls.Add(this.txtManagerID);
            this.grpBoxContent.Controls.Add(this.txtJobID);
            this.grpBoxContent.Controls.Add(this.txtHireDate);
            this.grpBoxContent.Controls.Add(this.txtLastName);
            this.grpBoxContent.Controls.Add(this.txtFirstName);
            this.grpBoxContent.Controls.Add(this.lbCommisionPCT);
            this.grpBoxContent.Controls.Add(this.lbDepartmentID);
            this.grpBoxContent.Controls.Add(this.label3);
            this.grpBoxContent.Controls.Add(this.lbJobID);
            this.grpBoxContent.Controls.Add(this.lbSalary);
            this.grpBoxContent.Controls.Add(this.lbManagerID);
            this.grpBoxContent.Controls.Add(this.lbEmail);
            this.grpBoxContent.Controls.Add(this.lbHireDate);
            this.grpBoxContent.Controls.Add(this.lbLastName);
            this.grpBoxContent.Controls.Add(this.lbFirstName);
            this.grpBoxContent.Location = new System.Drawing.Point(13, 121);
            this.grpBoxContent.Name = "grpBoxContent";
            this.grpBoxContent.Size = new System.Drawing.Size(764, 273);
            this.grpBoxContent.TabIndex = 0;
            this.grpBoxContent.TabStop = false;
            this.grpBoxContent.Text = "[조회내용]";
            // 
            // txtPhoneNumber
            // 
            this.txtPhoneNumber.Location = new System.Drawing.Point(550, 64);
            this.txtPhoneNumber.Name = "txtPhoneNumber";
            this.txtPhoneNumber.Size = new System.Drawing.Size(198, 21);
            this.txtPhoneNumber.TabIndex = 2;
            // 
            // txtEmail
            // 
            this.txtEmail.Location = new System.Drawing.Point(340, 64);
            this.txtEmail.Name = "txtEmail";
            this.txtEmail.Size = new System.Drawing.Size(198, 21);
            this.txtEmail.TabIndex = 2;
            // 
            // txtCommisionPCT
            // 
            this.txtCommisionPCT.Location = new System.Drawing.Point(550, 141);
            this.txtCommisionPCT.Name = "txtCommisionPCT";
            this.txtCommisionPCT.Size = new System.Drawing.Size(134, 21);
            this.txtCommisionPCT.TabIndex = 2;
            // 
            // txtSalary
            // 
            this.txtSalary.Location = new System.Drawing.Point(341, 141);
            this.txtSalary.Name = "txtSalary";
            this.txtSalary.Size = new System.Drawing.Size(134, 21);
            this.txtSalary.TabIndex = 2;
            // 
            // txtDepartmentID
            // 
            this.txtDepartmentID.Location = new System.Drawing.Point(181, 223);
            this.txtDepartmentID.Name = "txtDepartmentID";
            this.txtDepartmentID.Size = new System.Drawing.Size(134, 21);
            this.txtDepartmentID.TabIndex = 2;
            // 
            // txtManagerID
            // 
            this.txtManagerID.Location = new System.Drawing.Point(21, 223);
            this.txtManagerID.Name = "txtManagerID";
            this.txtManagerID.Size = new System.Drawing.Size(134, 21);
            this.txtManagerID.TabIndex = 2;
            // 
            // txtJobID
            // 
            this.txtJobID.Location = new System.Drawing.Point(181, 141);
            this.txtJobID.Name = "txtJobID";
            this.txtJobID.Size = new System.Drawing.Size(134, 21);
            this.txtJobID.TabIndex = 2;
            // 
            // txtHireDate
            // 
            this.txtHireDate.Location = new System.Drawing.Point(21, 141);
            this.txtHireDate.Name = "txtHireDate";
            this.txtHireDate.Size = new System.Drawing.Size(134, 21);
            this.txtHireDate.TabIndex = 2;
            // 
            // txtLastName
            // 
            this.txtLastName.Location = new System.Drawing.Point(181, 64);
            this.txtLastName.Name = "txtLastName";
            this.txtLastName.Size = new System.Drawing.Size(134, 21);
            this.txtLastName.TabIndex = 2;
            // 
            // txtFirstName
            // 
            this.txtFirstName.Location = new System.Drawing.Point(21, 64);
            this.txtFirstName.Name = "txtFirstName";
            this.txtFirstName.Size = new System.Drawing.Size(134, 21);
            this.txtFirstName.TabIndex = 2;
            // 
            // lbCommisionPCT
            // 
            this.lbCommisionPCT.AutoSize = true;
            this.lbCommisionPCT.Location = new System.Drawing.Point(564, 116);
            this.lbCommisionPCT.Name = "lbCommisionPCT";
            this.lbCommisionPCT.Size = new System.Drawing.Size(114, 12);
            this.lbCommisionPCT.TabIndex = 1;
            this.lbCommisionPCT.Text = "Commission PCT :";
            // 
            // lbDepartmentID
            // 
            this.lbDepartmentID.AutoSize = true;
            this.lbDepartmentID.Location = new System.Drawing.Point(195, 198);
            this.lbDepartmentID.Name = "lbDepartmentID";
            this.lbDepartmentID.Size = new System.Drawing.Size(92, 12);
            this.lbDepartmentID.TabIndex = 1;
            this.lbDepartmentID.Text = "Department ID :";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(599, 39);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(98, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "Phone Number :";
            // 
            // lbJobID
            // 
            this.lbJobID.AutoSize = true;
            this.lbJobID.Location = new System.Drawing.Point(222, 116);
            this.lbJobID.Name = "lbJobID";
            this.lbJobID.Size = new System.Drawing.Size(48, 12);
            this.lbJobID.TabIndex = 1;
            this.lbJobID.Text = "Job ID :";
            // 
            // lbSalary
            // 
            this.lbSalary.AutoSize = true;
            this.lbSalary.Location = new System.Drawing.Point(387, 116);
            this.lbSalary.Name = "lbSalary";
            this.lbSalary.Size = new System.Drawing.Size(49, 12);
            this.lbSalary.TabIndex = 1;
            this.lbSalary.Text = "Salary :";
            // 
            // lbManagerID
            // 
            this.lbManagerID.AutoSize = true;
            this.lbManagerID.Location = new System.Drawing.Point(49, 198);
            this.lbManagerID.Name = "lbManagerID";
            this.lbManagerID.Size = new System.Drawing.Size(78, 12);
            this.lbManagerID.TabIndex = 1;
            this.lbManagerID.Text = "Manager ID :";
            // 
            // lbEmail
            // 
            this.lbEmail.AutoSize = true;
            this.lbEmail.Location = new System.Drawing.Point(409, 39);
            this.lbEmail.Name = "lbEmail";
            this.lbEmail.Size = new System.Drawing.Size(45, 12);
            this.lbEmail.TabIndex = 1;
            this.lbEmail.Text = "Email :";
            // 
            // lbHireDate
            // 
            this.lbHireDate.AutoSize = true;
            this.lbHireDate.Location = new System.Drawing.Point(49, 116);
            this.lbHireDate.Name = "lbHireDate";
            this.lbHireDate.Size = new System.Drawing.Size(64, 12);
            this.lbHireDate.TabIndex = 1;
            this.lbHireDate.Text = "Hire Date :";
            // 
            // lbLastName
            // 
            this.lbLastName.AutoSize = true;
            this.lbLastName.Location = new System.Drawing.Point(212, 39);
            this.lbLastName.Name = "lbLastName";
            this.lbLastName.Size = new System.Drawing.Size(75, 12);
            this.lbLastName.TabIndex = 1;
            this.lbLastName.Text = "Last Name :";
            // 
            // lbFirstName
            // 
            this.lbFirstName.AutoSize = true;
            this.lbFirstName.Location = new System.Drawing.Point(49, 39);
            this.lbFirstName.Name = "lbFirstName";
            this.lbFirstName.Size = new System.Drawing.Size(75, 12);
            this.lbFirstName.TabIndex = 1;
            this.lbFirstName.Text = "First Name :";
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(647, 223);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(111, 40);
            this.btnOK.TabIndex = 0;
            this.btnOK.Text = "확인";
            this.btnOK.UseVisualStyleBackColor = true;
            // 
            // btnSearchAll
            // 
            this.btnSearchAll.Location = new System.Drawing.Point(13, 410);
            this.btnSearchAll.Name = "btnSearchAll";
            this.btnSearchAll.Size = new System.Drawing.Size(144, 47);
            this.btnSearchAll.TabIndex = 2;
            this.btnSearchAll.Text = "전체 조회";
            this.btnSearchAll.UseVisualStyleBackColor = true;
            this.btnSearchAll.Click += new System.EventHandler(this.BtnSearchAll_Click);
            // 
            // listAllEmployees
            // 
            this.listAllEmployees.Location = new System.Drawing.Point(176, 410);
            this.listAllEmployees.Name = "listAllEmployees";
            this.listAllEmployees.Size = new System.Drawing.Size(585, 221);
            this.listAllEmployees.TabIndex = 3;
            this.listAllEmployees.UseCompatibleStateImageBehavior = false;
            this.listAllEmployees.View = System.Windows.Forms.View.Details;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(815, 674);
            this.Controls.Add(this.listAllEmployees);
            this.Controls.Add(this.btnSearchAll);
            this.Controls.Add(this.grpBoxContent);
            this.Controls.Add(this.grpBoxView);
            this.Name = "MainForm";
            this.Text = "직원조회";
            this.grpBoxView.ResumeLayout(false);
            this.grpBoxView.PerformLayout();
            this.grpBoxContent.ResumeLayout(false);
            this.grpBoxContent.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpBoxView;
        private System.Windows.Forms.GroupBox grpBoxContent;
        private System.Windows.Forms.Button btnView;
        private System.Windows.Forms.Label lbEmployeeID;
        private System.Windows.Forms.TextBox txtBoxEmployeeID;
        private System.Windows.Forms.TextBox txtPhoneNumber;
        private System.Windows.Forms.TextBox txtEmail;
        private System.Windows.Forms.TextBox txtLastName;
        private System.Windows.Forms.TextBox txtFirstName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lbEmail;
        private System.Windows.Forms.Label lbLastName;
        private System.Windows.Forms.Label lbFirstName;
        private System.Windows.Forms.TextBox txtCommisionPCT;
        private System.Windows.Forms.TextBox txtSalary;
        private System.Windows.Forms.TextBox txtJobID;
        private System.Windows.Forms.TextBox txtHireDate;
        private System.Windows.Forms.Label lbCommisionPCT;
        private System.Windows.Forms.Label lbJobID;
        private System.Windows.Forms.Label lbSalary;
        private System.Windows.Forms.Label lbHireDate;
        private System.Windows.Forms.TextBox txtDepartmentID;
        private System.Windows.Forms.TextBox txtManagerID;
        private System.Windows.Forms.Label lbDepartmentID;
        private System.Windows.Forms.Label lbManagerID;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnSearchAll;
        private System.Windows.Forms.ListView listAllEmployees;
    }
}

